#pragma once

#include "SimpleNode.h"

class SPAWNPEDESTRIAN_API FSpawnManager
{
public:
	FSpawnManager();

	void InitializeNavMesh();
	void InitializePedestrian();

	// UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MyOwnCategory")
	void SpawnPedestrian(FVector StartLocation) const;

protected:
	static AVolume* DummySpawnBoxedVolume(FVector Origin, FVector BoxExtend, bool bIsNavMeshBound = false);


private:
	// Store the blueprint pedestrian character, need to be initialized in the constructor
	UBlueprint* PedestrianCharacterBP;

	// Store A list of possible moveable points.
	TArray<FVector> SideWalkCenters;
};
