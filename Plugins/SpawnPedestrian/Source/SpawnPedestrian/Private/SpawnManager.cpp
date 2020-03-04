#include "SpawnManager.h"

#include "Atmosphere/AtmosphericFog.h"
#include "Engine/SkyLight.h"
#include "Components/SkyLightComponent.h"

#include "EngineUtils.h"
#include "Engine/StaticMeshActor.h"
#include "Builders/CubeBuilder.h"
#include "EditorModeManager.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NavigationSystem.h"
#include "IPluginManager.h"
#include "NavModifierVolume.h"
#include "NavArea_Obstacle.h"

#define DEBUG_PRINT(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)

FSpawnManager::FSpawnManager()
{
	UE_LOG(LogTemp, Warning, TEXT("SpawnManager::SpawnManager() Called."));

	NavMeshOrigin = FVector::ZeroVector;
	NavMeshExtend = FVector(4096.0f, 8192.0f, 256.0f);
}

void FSpawnManager::InitializeMap() const
{
	UWorld* World = GEditor->GetEditorWorldContext().World();

	const FVector Location = FVector(0.0f, 0.0f, 2000.0f);
	const FVector LightLocation = FVector(0.0f, 0.0f, 100000.0f);

	World->SpawnActor<AAtmosphericFog>(Location, FRotator::ZeroRotator);

	const ASkyLight* Skylight = World->SpawnActor<ASkyLight>(LightLocation, FRotator::ZeroRotator);
	if (Skylight != nullptr)
	{
		Skylight->GetLightComponent()->SetIntensity(5.0f);
		GEditor->BuildLighting(LightOptions);
	}
}

void FSpawnManager::InitializeNavMesh() const
{
	UWorld* World = GEditor->GetEditorWorldContext().World();

	DummySpawnBoxedVolume(FVector::ZeroVector, FVector{8192.0f, 20480.0f, 512.0f}, TEXT("NavMeshBoundsVolume"));

	for (TActorIterator<AStaticMeshActor> ActorItr(World); ActorItr; ++ActorItr)
	{
		FVector Origin;
		FVector Bounds;
		ActorItr->GetActorBounds(false, Origin, Bounds);
		Bounds += FVector(0.0f, 0.0f, 512.0f);

		// TODO: Remove this part, this is temporary
		auto a = ActorItr->GetName();
		if (ActorItr->GetName().Compare(FString{"Road"}))
		{
			//DummySpawnBoxedVolume(Origin, Bounds * 2, TEXT("NavMeshBoundsVolume"));
		}
		else
		{
			FVector Half = FVector{0.0f, Bounds.Y / 2, 0.0f};
			Bounds.X *= 2;

			FVector NewOrigin = Origin - Half;
			NewOrigin.Y -= 512.0f;
			DummySpawnBoxedVolume(NewOrigin, Bounds, TEXT("NavModifierVolume"));

			NewOrigin = Origin + Half;
			NewOrigin.Y += 512.0f;


			DummySpawnBoxedVolume(NewOrigin, Bounds, TEXT("NavModifierVolume"));

			for (TActorIterator<ANavModifierVolume> VolumeItr(World); VolumeItr; ++VolumeItr)
			{
				VolumeItr->SetAreaClass(UNavArea_Obstacle::StaticClass());
			}
		}
	}
}

void FSpawnManager::InitializePedestrian() const
{
	UWorld* World = GEditor->GetEditorWorldContext().World();

	// Currently spawning one pedestrian at random position.
	// TODO: Spawn more
	const FVector NewLocation = UKismetMathLibrary::RandomPointInBoundingBox(
		NavMeshOrigin, NavMeshExtend);
}

FString FSpawnManager::InContent(const FString& RelativePath)
{
	static FString ContentDir = IPluginManager::Get().FindPlugin(TEXT("SpawnPedestrian"))->GetContentDir();

	return ContentDir / RelativePath;
}

void FSpawnManager::DummySpawnBoxedVolume(FVector Origin, FVector BoxExtend, TCHAR* VolumeClassName)
{
	UWorld* World = GEditor->GetEditorWorldContext().World();
	ABrush* WorldBrush = World->GetDefaultBrush();

	// Cube Additive Brush
	UCubeBuilder* CubeAdditiveBrushBuilder = Cast<UCubeBuilder>(
		GEditor->FindBrushBuilder(UCubeBuilder::StaticClass()));

	CubeAdditiveBrushBuilder->X = BoxExtend.X;
	CubeAdditiveBrushBuilder->Y = BoxExtend.Y;
	CubeAdditiveBrushBuilder->Z = BoxExtend.Z;
	CubeAdditiveBrushBuilder->Build(World);

	//GEditor->Exec(World, TEXT("BRUSH MOVETO X=0 Y=0 Z=0"));
	WorldBrush->Modify();
	WorldBrush->SetActorLocation(Origin, false);

	// GEditor->Exec(World, TEXT("BRUSH ADDVOLUME CLASS=NavMeshVolume"));
	TArray<FStringFormatArg> Args;
	Args.Add(FStringFormatArg(VolumeClassName));
	const auto Cmd = FString::Format(TEXT("BRUSH ADDVOLUME CLASS={0}"), Args);
	GEditor->Exec(World, ToCStr(Cmd));

	GLevelEditorModeTools().MapChangeNotify();
}
