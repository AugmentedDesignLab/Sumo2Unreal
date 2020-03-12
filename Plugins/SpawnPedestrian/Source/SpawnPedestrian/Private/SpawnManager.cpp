#include "SpawnManager.h"

#include "EngineUtils.h"
#include "EditorModeManager.h"
#include "NavigationSystem.h"
#include "Builders/CubeBuilder.h"

#include "BSPOps.h"
#include "NavMeshBoundsVolume.h"
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
		FVector{10000.0f, -10000.0f, 0.0f}, FVector{40000.0f, 40000.0f, 512.0f}, true);

	// Iterate through sumo Actors
	for (TActorIterator<ARoadMesh> ActorItr(World); ActorItr; ++ActorItr)
	{
		if (ActorItr->currentMeshType == MeshType::Road)
		{
			FVector Origin;
			FVector Bounds;

			// Save the original rotation of the mesh
			const FRotator OriginalRotator = ActorItr->GetActorRotation();

			// Turn it to axis aligned, then get the bounds
			ActorItr->SetActorRotation(FRotator::ZeroRotator);
			ActorItr->GetActorBounds(true, Origin, Bounds);

			// double the base area, then lift it up
			Bounds.Z += 512.0f;
			Bounds.X *= 2;
			Bounds.Y *= 2;


			AVolume* SpawnedVolume = DummySpawnBoxedVolume(Origin, Bounds);

			// Restore the rotator of both
			SpawnedVolume->SetActorRotation(OriginalRotator);
			ActorItr->SetActorRotation(OriginalRotator);
		}
	}

	for (TActorIterator<ANavModifierVolume> VolumeItr(World); VolumeItr; ++VolumeItr)
	{
		VolumeItr->SetAreaClass(UNavArea_Obstacle::StaticClass());
	}

	GLevelEditorModeTools().MapChangeNotify();
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

AVolume* FSpawnManager::DummySpawnBoxedVolume(FVector Origin, FVector BoxExtend, bool bIsNavMeshBound)
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
	WorldBrush->SetActorRotation(FRotator::ZeroRotator);


	//// GEditor->Exec(World, TEXT("BRUSH ADDVOLUME CLASS=NavMeshVolume"));
	//TArray<FStringFormatArg> Args;
	//Args.Add(FStringFormatArg(VolumeClassName));
	//const auto Cmd = FString::Format(TEXT("BRUSH ADDVOLUME CLASS={0}"), Args);
	//GEditor->Exec(World, ToCStr(Cmd));

	UClass* VolumeClass = bIsNavMeshBound ? ANavMeshBoundsVolume::StaticClass() : ANavModifierVolume::StaticClass();

	const FVector SpawnLoc = WorldBrush->GetActorLocation();
	AVolume* Actor = World->SpawnActor<AVolume>(VolumeClass, SpawnLoc, FRotator::ZeroRotator);
	if (Actor)
	{
		Actor->PreEditChange(nullptr);

		FBSPOps::csgCopyBrush
		(
			Actor,
			WorldBrush,
			0,
			RF_Transactional,
			true,
			true
		);

		// Set the texture on all polys to NULL.  This stops invisible texture
		// dependencies from being formed on volumes.
		if (Actor->Brush)
		{
			for (int32 poly = 0; poly < Actor->Brush->Polys->Element.Num(); ++poly)
			{
				FPoly* Poly = &(Actor->Brush->Polys->Element[poly]);
				Poly->Material = nullptr;
			}
		}
		Actor->PostEditChange();
	}

	if (Actor)
	{
		ULevel::LevelDirtiedEvent.Broadcast();
		World->BroadcastLevelsChanged();
	}

	GLevelEditorModeTools().MapChangeNotify();

	return Actor;
}

void FSpawnManager::SpawnPedestrian(const FVector StartLocation, FVector EndLocation) const
{
	UWorld* World = GEditor->GetEditorWorldContext().World();

	// Spawn the character at start location
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	AActor* Pedestrian = World->SpawnActor<AActor>(
		PedestrianCharacterBP->GeneratedClass, StartLocation, FRotator::ZeroRotator, SpawnParams);

	// Readjust the location (lift above the ground)
	Pedestrian->SetActorLocation(StartLocation + FVector{0.0f, 0.0f, 128.0f});

	// Then set the end location for the character
}
