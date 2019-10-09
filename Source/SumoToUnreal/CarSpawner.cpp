// Fill out your copyright notice in the Description page of Project Settings.

#include "CarSpawner.h"

#include "Engine.h"


// Sets default values
ACarSpawner::ACarSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ACarSpawner::Spawn(FVector Location)
{
	if (ToSpawn)
	{
		Location = this->GetActorLocation();
		UWorld* world = GetWorld();
		if (world)
		{
			FActorSpawnParameters spawn_param;
			spawn_param.Owner = this;
			FRotator rotator;
			world->SpawnActor<AVehicleMovement>(ToSpawn, Location, rotator, spawn_param);
		}
	}
}

// Called when the game starts or when spawned
void ACarSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACarSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SpawnTimer += DeltaTime;

	if (SpawnTimer > 5.0f)
	{
		Spawn(FVector(0.0, 0.0, 0.0));
		SpawnTimer = 0.0;
	}
}

