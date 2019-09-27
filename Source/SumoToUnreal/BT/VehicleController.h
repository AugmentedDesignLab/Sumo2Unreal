// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include <vector>
#include "VehicleMovement.h"
#include <Runtime\AIModule\Classes\Perception\AIPerceptionComponent.h>
#include <Runtime\AIModule\Classes\Perception\AISenseConfig_Sight.h>
#include <Runtime\AIModule\Classes\BehaviorTree\BehaviorTreeComponent.h>
#include <Runtime\AIModule\Classes\BehaviorTree\BlackboardComponent.h>
#include "VehicleController.generated.h"


/**
 * 
 */

struct FVectorSortByDistance
{
	FVectorSortByDistance(const FVector& InSourceLocation) : SourceLocation(InSourceLocation)
	{

	}

	/* The Location to use in our Sort comparision. */
	FVector SourceLocation;

	bool operator()(const FVector A, const FVector B) const
	{
		float DistanceA = FVector::DistSquared(SourceLocation, A);
		float DistanceB = FVector::DistSquared(SourceLocation, B);

		return DistanceA < DistanceB;
	}
};


UCLASS()
class SUMOTOUNREAL_API AVehicleController : public AAIController
{
	GENERATED_BODY()

public:
	AVehicleController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:

	void Tick(float DeltaTime) override;

	/*
	using a forum post template
		https://forums.unrealengine.com/community/community-content-tools-and-tutorials/188-behavior-tree-tutorial?130-Behavior-Tree-Tutorial=&highlight=mikepurvis%20AI%20Behavior%20Tree
	*/

	UPROPERTY(transient)
		UBlackboardComponent* BlackboardComp;

	UPROPERTY(transient)
		UBehaviorTreeComponent* BehaviorComp;

	UPROPERTY(transient)
		UAIPerceptionComponent* AIPerceptionComp;

	UPROPERTY(transient)
		UAISenseConfig_Sight* AIPerceptionSigntComp;



	///variables

	TArray<FVector> StopSignLocation; //all the stop sign location
	TArray<AVehicleMovement*> OtherVehicle; // All the vehicles in the scene
	AVehicleMovement* OtherVehicleOnSpline; // All the vehicles using the same spline
	float SpeedLimit = 0.0;
	AVehicleMovement* Vehicle; // vechicle movement for this controller


	///state boolean

	bool IsNormalRoad = true; // when no near stop sign and car then true
	bool IsVehicleAhead = true; // check vehicles on the same spline
	bool IsChangeSplineAhead = false; // check if end of spline reached (threshold required)



	///Functions

	UFUNCTION()
	AVehicleMovement* GetVehicleFromController();
	UFUNCTION(BlueprintCallable)
	void VahicleBrake(float BrakeValue);
	UFUNCTION()
	void ProcessPerceivedInformation(const TArray<AActor*>& UpdatedActors);

	float Move(float Speed);
	float Stop(float Speed);
	void PrintLog(FString Text);
	float CalculateSteeringValue(float delta);

};
