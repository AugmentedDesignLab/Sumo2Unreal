// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WheeledVehicleObject.h"
#include "Engine.h"
#include "VehicleSpawner.generated.h"

USTRUCT()
struct FVehicleSpecification
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AWheeledVehicleObject> VehicleObject;

	UPROPERTY(EditAnywhere)
	AWayPoint* Spline;

	UPROPERTY(EditAnywhere)
	float SpawnDistanceOnSpline;

	UPROPERTY(EditAnywhere)
	float SpawnAfterSec;
	
};



UCLASS()
class SUMOTOUNREAL_API AVehicleSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVehicleSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/*
	 * spawn a vehicle with a given vehicle object, waypoint,  distance along spline and a spawn height. detects the orientation while spawning.
	 */
	UFUNCTION()
	APawn* SpawnVehicle(TSubclassOf<class AWheeledVehicleObject> VehicleObject, AWayPoint* WayPoint, float DistanceAlongSpline, float SpawnHeight);

	UFUNCTION()
	TArray<AActor*> FindAllWaypoint();

	UPROPERTY(EditAnywhere)
	TArray<FVehicleSpecification> VehicleList;

	
	TArray<AActor*> SplineActors;
	TArray<AWayPoint*> Waypoints;

	// local variable
	float temp = 0;
	int spawning = 0;


	UFUNCTION()
	void PrintLog(FString Text)
	{
		if (!GEngine) return;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, *Text);
	}

	/*
	 * comparison operator for sorting by spawntime. 
	 */
	inline static bool Comparison(const FVehicleSpecification& ip1, const FVehicleSpecification& ip2)
	{
		return (ip1.SpawnAfterSec < ip2.SpawnAfterSec);
	}


};
