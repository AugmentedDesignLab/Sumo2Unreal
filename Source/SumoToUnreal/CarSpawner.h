// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BT/VehicleMovement.h"
#include "CarSpawner.generated.h"

UCLASS()
class SUMOTOUNREAL_API ACarSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACarSpawner();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AVehicleMovement> ToSpawn;

	UFUNCTION()
	void Spawn(FVector Location);

	UPROPERTY(EditAnywhere)
	TArray<int> CarSpawningSpline;

	UPROPERTY(EditAnywhere)
	float SpawnTimer = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
