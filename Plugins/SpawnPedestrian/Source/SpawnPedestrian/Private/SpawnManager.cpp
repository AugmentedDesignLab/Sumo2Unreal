#include "SpawnManager.h"

#include "EngineUtils.h"
#include "EditorModeManager.h"
#include "NavigationSystem.h"
#include "Builders/CubeBuilder.h"

#include "NavModifierVolume.h"
#include "NavArea_Obstacle.h"

// Sumo2Unreal
#include "RoadMesh.h"

#define DEBUG_PRINT(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)

FSpawnManager::FSpawnManager()
{
	UE_LOG(LogTemp, Warning, TEXT("SpawnManager::SpawnManager() Called."));

	UObject* SpawnActor = Cast<UObject>(
		StaticLoadObject(UObject::StaticClass(), nullptr,
		                 TEXT(
			                 "Blueprint'/SpawnPedestrian/BasePedestrian/Blueprints/BP_PedestrianCharacter.BP_PedestrianCharacter'")));

	PedestrianCharacterBP = Cast<UBlueprint>(SpawnActor);
	if (!SpawnActor)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
		return;
	}

	UClass* SpawnClass = SpawnActor->StaticClass();
	if (SpawnClass == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CLASS == NULL")));
		return;
	}
}

void FSpawnManager::InitializeNavMesh()
{
	UWorld* World = GEditor->GetEditorWorldContext().World();

	DummySpawnBoxedVolume(
		FVector{10000.0f, -10000.0f, 0.0f}, FVector{40000.0f, 40000.0f, 512.0f}, TEXT("NavMeshBoundsVolume"));

	// Iterate through sumo Actors
	for (TActorIterator<ARoadMesh> ActorItr(World); ActorItr; ++ActorItr)
	{
		if (ActorItr->currentMeshType == MeshType::Road)
		{
			FVector Origin;
			FVector Bounds;
			ActorItr->GetActorBounds(true, Origin, Bounds);

			Bounds.Z += 512.0f;
			Bounds.X *= 2;
			Bounds.Y *= 2;

			DummySpawnBoxedVolume(Origin, Bounds, TEXT("NavModifierVolume"));
		}
	}

	for (TActorIterator<ANavModifierVolume> VolumeItr(World); VolumeItr; ++VolumeItr)
	{
		VolumeItr->SetAreaClass(UNavArea_Obstacle::StaticClass());
	}
}

void FSpawnManager::InitializePedestrian()
{
	UWorld* World = GEditor->GetEditorWorldContext().World();

	for (TActorIterator<ARoadMesh> ActorItr(World); ActorItr; ++ActorItr)
	{
		if (ActorItr->currentMeshType == MeshType::Sidewalk)
		{
			SideWalkCenters.Add(ActorItr->GetActorLocation());
		}
	}

	const FVector Start = SideWalkCenters[FMath::RandRange(0, SideWalkCenters.Num() - 1)];
	FVector End = SideWalkCenters[FMath::RandRange(0, SideWalkCenters.Num() - 1)];

	SpawnPedestrian(Start, Start);
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

	// GEditor->Exec(World, TEXT("BRUSH MOVETO X=0 Y=0 Z=0"));
	WorldBrush->Modify();
	WorldBrush->SetActorLocation(Origin, false);

	// GEditor->Exec(World, TEXT("BRUSH ADDVOLUME CLASS=NavMeshVolume"));
	TArray<FStringFormatArg> Args;
	Args.Add(FStringFormatArg(VolumeClassName));
	const auto Cmd = FString::Format(TEXT("BRUSH ADDVOLUME CLASS={0}"), Args);
	GEditor->Exec(World, ToCStr(Cmd));

	GLevelEditorModeTools().MapChangeNotify();
}

void FSpawnManager::SpawnPedestrian(const FVector StartLocation, FVector EndLocation) const
{
	UWorld* World = GEditor->GetEditorWorldContext().World();

	// Spawn the character at start location
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	World->SpawnActor<AActor>(
		PedestrianCharacterBP->GeneratedClass, StartLocation, FRotator::ZeroRotator, SpawnParams);

	// Then set the end location for the character
}
