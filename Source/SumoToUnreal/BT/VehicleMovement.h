// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicle.h"
#include "WayPoint.h"
#include <Runtime\AIModule\Classes\Perception\AIPerceptionComponent.h>
#include <Runtime\AIModule\Classes\BehaviorTree\BehaviorTree.h>
#include "Classes/Components/SplineComponent.h"
#include "WheeledVehicleMovementComponent4W.h"
#include "VehicleMovement.generated.h"



USTRUCT()
struct FVehicleControl
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float SteeringValue;

	UPROPERTY(EditAnywhere)
	float ThrottleValue;

	UPROPERTY(EditAnywhere)
	float BrakeValue;

	UPROPERTY(EditAnywhere)
	float DistanceThreshold;

	UPROPERTY(EditAnywhere)
	float TraveledDistance;

	UPROPERTY(EditAnywhere)
	AWayPoint *WayPoint;

	UPROPERTY(EditAnywhere)
	float SpeedLimit;


};



UCLASS()
class SUMOTOUNREAL_API AVehicleMovement : public AWheeledVehicle
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AVehicleMovement();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//control getter

	FVehicleControl& GetLastControl();

	FTransform GetVehicleTransform();

	FVector GetVehicleLocation();
	
	FVector GetVehicleForward();

	FVector GetVehicleVelocity();
	
	float GetTraveledDistance();
	
	float GetSpeedLimit();

	AWayPoint* GetWayPoint();

	void SetLocation(FVector Location);

	void SetControl();

	void SetSteeringValue(float SteeringValue);

	void SetThrottleValue(float ThrottleValue);

	void SetBrakeValue(float BrakeValue);

	void SetWayPoint(AWayPoint* WayPoint);

	void SetSpeedLimit(float SpeedLimit);

	void SetTraveledDistance(float Distance);


	/*
		Variables
	*/
	
	UPROPERTY(EditAnywhere)
	FVehicleControl LastControl;

	UPROPERTY(EditAnywhere)
	UBehaviorTree* VehicleBehavior;

	void PrintLog(FString text);

	

	float Time = 0.0f;



};
