#pragma once

#include "SimpleNode.h"

class SPAWNPEDESTRIAN_API FSpawnManager
{
public:
	/**
	 * \brief Must be called before calling any spawn pedestrian function.
	 */
	static void LoadBlueprintAssets();

	/**
	 * \brief Generate both NavMesh bounds and NavMesh modifiers.
	 */
	static void InitializeNavMesh();

	/**
	 * \brief This function is designed to be called by the Scenario Generator. But it can be called by
	 * other part of code as well.
	 * \param InWorld The world which you are spawning in. 
	 * \param SpawnLocation ALocation you want to spawn the pedestrian
	 * \return The spawned Pedestrian actor
	 */
	static AActor* SpawnPedestrianOn(UWorld* InWorld, FVector SpawnLocation);

protected:
	
	static AVolume* DummySpawnBoxedVolume(FVector Origin, FVector BoxExtend, bool bIsNavMeshBound = false);

private:

	/**
	 * \brief Storing a reference to the loaded Blueprint Object
	 */
	static UBlueprint* PedestrianCharacterBlueprint;

	//TArray<FVector> SideWalkCenters;
};
