// Fill out your copyright notice in the Description page of Project Settings.


#include "WheeledVehicleObject.h"
#include <Runtime\AIModule\Classes\BehaviorTree\BlackboardComponent.h>
#include "WheeledVehicleMovementComponent4W.h"
#include "GameFramework/Pawn.h"

//runs first when simulate
AWheeledVehicleObject::AWheeledVehicleObject()
{
	PrimaryActorTick.bCanEverTick = true;
	PrintLog("Inside vehicle object constructor ");
}

//runs fourth time
void AWheeledVehicleObject::BeginPlay()
{
	Super::BeginPlay();

	PrintLog("Inside vehicle object beginplay");
	
	VehicleAIController = GetController<AVehicleAIController>();
	BlackBoardData = VehicleAIController->BlackboardComp;
	if (BlackBoardData == NULL && VehicleAIController == NULL) return;

	//setting up variable in the blackboard
	BlackBoardData->SetValueAsObject("WayPoint", WayPoint);
	BlackBoardData->SetValueAsObject("VehicleObject", this);
	
	
}

void AWheeledVehicleObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//PrintLog("Inside vehicle object tick");
	
	float brake_value = BlackBoardData->GetValueAsFloat("BrakeValue");
	float steer_value = BlackBoardData->GetValueAsFloat("SteerValue");
	float throttle_value = BlackBoardData->GetValueAsFloat("ThrottleValue");
	
	this->GetVehicleMovement()->SetBrakeInput(brake_value);
	this->GetVehicleMovement()->SetSteeringInput(steer_value);
	this->GetVehicleMovement()->SetThrottleInput(throttle_value);
	
	
}
