// Fill out your copyright notice in the Description page of Project Settings.
// debug color RED
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

	/**
	* returns the updated steering value. takes the elapsed delta time as para. 
	*/
	float UpdatedSteeringValue(float Delta);

	/**
	* Init the BT. if T then successfully got the BT from the given path. initialize Blackboard inside. Should
	* do in a way so that it reads a xml. which is like a  driver profile.
	*/
	bool InitializeBehaviorTree(FString BTPath);

	/**
	* Called from another script. Some init is happening in WheeledVehicleObject file. 
	*/
	bool RunBehaviorTree();

	/*
	 * get the velocity. velocity gets updated inside the UpdatedSteeringValue() 
	 */
	FVector GetVehicleVelocity();
	
	UPROPERTY()
	UBlackboardComponent* BlackboardComponent;
	UPROPERTY()
	UBehaviorTreeComponent* BehaviorTreeComponent;
	UPROPERTY()
	UBehaviorTree* BehaviorTreeAsset;
	UPROPERTY()
	AWayPoint* WayPoint;
	UPROPERTY()
	FVector VehicleVelocity;

	



	//Function to load object from content folder. Copy path from UE
	template <typename ObjClass>
	static FORCEINLINE ObjClass* LoadObjFromPath(const FName& Path)
	{
		if (Path == NAME_None) return NULL;

		return Cast<ObjClass>(StaticLoadObject(ObjClass::StaticClass(), NULL, *Path.ToString()));

	}

	void PrintLog(FString Text) 
	{
		if (!GEngine) return;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, *Text);
	}

};
