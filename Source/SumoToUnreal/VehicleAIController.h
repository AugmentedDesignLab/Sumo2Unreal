// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Engine.h"
#include "WayPoint.h"
#include <Runtime\AIModule\Classes\BehaviorTree\BehaviorTreeComponent.h>
#include <Runtime\AIModule\Classes\BehaviorTree\BlackboardComponent.h>
#include "WheeledVehicle.h"
#include "VehicleAIController.generated.h"

/**
 * 
 */
UCLASS()
class SUMOTOUNREAL_API AVehicleAIController : public AAIController
{
	GENERATED_BODY()

public:
	AVehicleAIController();

protected:
	virtual void BeginPlay() override;

public:
	void Tick(float DeltaTime) override;

	UPROPERTY()
	UBlackboardComponent* BlackboardComp;
	UPROPERTY()
	UBehaviorTreeComponent* BehaviorComp;
	UPROPERTY()
	AWayPoint* WayPoint;
	UPROPERTY()
	float DistanceAlongWayPoint = 0.0;

	float UpdatedSteeringValue(float Delta);


	//Function to load object from content folder
	template <typename ObjClass>
	static FORCEINLINE ObjClass* LoadObjFromPath(const FName& Path)
	{
		if (Path == NAME_None) return NULL;
		//~

		return Cast<ObjClass>(StaticLoadObject(ObjClass::StaticClass(), NULL, *Path.ToString()));
	}

	void PrintLog(FString Text) 
	{
		if (!GEngine) return;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, *Text);
	}

};
