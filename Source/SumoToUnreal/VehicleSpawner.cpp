// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleSpawner.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

AVehicleSpawner::AVehicleSpawner()
   : Iteration(5),
     TimeToSpawn(5.f)
{
   PrimaryActorTick.bCanEverTick = true;
}

void AVehicleSpawner::BeginPlay()
{
   Super::BeginPlay();
}

void AVehicleSpawner::Tick(float DeltaTime)
{
   Super::Tick(DeltaTime);

   TimeToSpawn -= DeltaTime;

   if (Iteration > 0 && TimeToSpawn < 0.f)
   {
      Spawn();

      Iteration = 0;
   }
}

void AVehicleSpawner::Spawn()
{
   if (!ToSpawn)
   {
      return;
   }

   GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "AVehicleSpawner::Spawn");

   auto World = GetWorld();
   if (World)
   {
      const auto SpawnLocation = FVector::ZeroVector;
      FActorSpawnParameters SpawnParams;
      SpawnParams.Owner = this;

      World->SpawnActor<ABasicVehicle>(ToSpawn, SpawnLocation, {}, SpawnParams);
   }
}
