// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleSpawner.h"
#include "Engine/World.h"

AVehicleSpawner::AVehicleSpawner()
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
}

void AVehicleSpawner::Spawn()
{
   if (!ToSpawn)
   {
      return;
   }

   UE_LOG(LogTemp, Display, TEXT("AVehicleSpawner::Spawn"))

   auto World = GetWorld();
   if (World)
   {
      const auto SpawnLocation = FVector::ZeroVector;
      FActorSpawnParameters SpawnParams;
      SpawnParams.Owner = this;

      World->SpawnActor<ABasicVehicle>(ToSpawn, SpawnLocation, {}, SpawnParams);
   }
}
