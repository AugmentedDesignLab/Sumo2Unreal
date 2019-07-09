// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicVehicle.generated.h"

UCLASS()
   class SUMOTOUNREAL_API ABasicVehicle : public AActor
{
   GENERATED_BODY()

public:
   ABasicVehicle();

protected:
   void BeginPlay() override;

public:
   void Tick(float DeltaTime) override;

   UPROPERTY(EditAnywhere)
   UStaticMeshComponent* Mesh;
};
