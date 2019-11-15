// Fill out your copyright notice in the Description page of Project Settings.


#include "WheeledVehicleObject.h"
#include <Runtime\AIModule\Classes\BehaviorTree\BlackboardComponent.h>
#include "WheeledVehicleMovementComponent4W.h"
#include "GameFramework/Pawn.h"

AWheeledVehicleObject::AWheeledVehicleObject()
{
	PrimaryActorTick.bCanEverTick = true;
	PrintLog("Inside constructor vehicle object");
}

void AWheeledVehicleObject::BeginPlay()
{
	Super::BeginPlay();

	PrintLog("Inside vehicle object begin play");
	VehicleAIController = GetController<AVehicleAIController>();
	BlackBoardData = VehicleAIController->BlackboardComp;
	if (BlackBoardData != NULL)
	{
		PrintLog("Not Null vehicle BB");
	}
	
}

void AWheeledVehicleObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//PrintLog("Inside wheeleded vehicle tick");
	
	float brake_value = BlackBoardData->GetValueAsFloat("BrakeValue");
	float steer_value = BlackBoardData->GetValueAsFloat("SteerValue");
	float throttle_value = BlackBoardData->GetValueAsFloat("ThrottleValue");
	
	this->GetVehicleMovement()->SetBrakeInput(brake_value);
	this->GetVehicleMovement()->SetSteeringInput(steer_value);
	this->GetVehicleMovement()->SetThrottleInput(throttle_value);
	
}
