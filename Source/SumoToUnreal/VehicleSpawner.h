// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicVehicle.h"
#include "GameFramework/Actor.h"
#include "VehicleSpawner.generated.h"

UCLASS()
   class SUMOTOUNREAL_API AVehicleSpawner : public AActor
{
   GENERATED_BODY()

public:
   AVehicleSpawner();

protected:
   void BeginPlay() override;

private:
   int Iteration;
   float TimeToSpawn;

public:
   void Tick(float DeltaTime) override;

   UPROPERTY(EditAnywhere, Category = "Spawner")
   TSubclassOf<class ABasicVehicle> ToSpawn;

   UFUNCTION(BlueprintCallable)
   void Spawn();
};
