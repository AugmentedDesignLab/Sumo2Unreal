// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicle.h"
#include "Engine.h"
#include "WayPoint.h"
#include "VehicleAIController.h"
#include <Runtime\AIModule\Classes\BehaviorTree\BehaviorTree.h>
#include "WheeledVehicleObject.generated.h"

/**
 * 
 */
UCLASS()
class SUMOTOUNREAL_API AWheeledVehicleObject : public AWheeledVehicle
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWheeledVehicleObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*
	 * get the distance along spline when get spawned. Make the code independent to spawn at any location
	 */
	float GetDistanceAlongSpline(FVector Location, USplineComponent* Spline);

	/*
	 * init the BT. Path address is not dynamic. need to set it as para. Move forward if only BT and BB are not null. Set
	 * some value in the BB. 
	 */
	bool InitializeWheeledVehicle(AWayPoint* WayPoint);

	/*
	 * destroying vehicle at the end of the spline. get called from the task.  
	 */
	bool SelfDestroy();
	
	UPROPERTY(EditAnywhere)
	AVehicleAIController* VehicleAIController;

	UBlackboardComponent* BlackBoard;

	UPROPERTY(EditAnywhere)
	AWayPoint* WayPoint;



	void PrintLog(FString Text)
	{
		if (!GEngine) return;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, *Text);
	}
};
