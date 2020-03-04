#pragma once

#include "Editor.h"
#include "LightingBuildOptions.h"
#include "PedestrianCharacter.h"

#include "SimpleNode.h"

class FSpawnManager
{
public:
	FSpawnManager();

	void InitializeMap() const;
	void InitializeNavMesh() const;
	void InitializePedestrian() const;

	static FString InContent(const FString& RelativePath);

	static void DummySpawnBoxedVolume(FVector Origin, FVector BoxExtend, TCHAR* VolumeClassName);

protected:

	TSubclassOf<ACharacter> ThirdPersonCharacterBP;
	TSubclassOf<APedestrianCharacter> PedestrianCharacterBP;

	// Here we have some information of the NavMesh
	// TODO: add a reference to NavMesh
	FVector NavMeshOrigin;
	FVector NavMeshExtend;
	// ANavMeshBoundsVolume

private:

	FLightingBuildOptions LightOptions;
};
