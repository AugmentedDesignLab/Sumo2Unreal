// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleAIController.h"
#include <Runtime\AIModule\Classes\BehaviorTree\BehaviorTree.h>


AVehicleAIController::AVehicleAIController()
{
	PrintLog("Inside the constructor");
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>("VehicleBlackBoard");
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>("VehicleBehaviorTree");
}

void AVehicleAIController::BeginPlay()
{
	Super::BeginPlay();

	PrintLog("Inside controller beginplay");
	
	UBehaviorTree* BehaviorTreeAsset = LoadObjFromPath<UBehaviorTree>(FName("'/Game/BehaviorTree/AI/BehaviorTree.BehaviorTree'"));
	if (BehaviorTreeAsset != NULL)
	{
		BlackboardComp->InitializeBlackboard(*BehaviorTreeAsset->BlackboardAsset);
		BehaviorComp->StartTree(*BehaviorTreeAsset);
	}
	else 
	{
		PrintLog("Behavior Asset not found");
		return;
	}

	BlackboardComp->SetValueAsFloat("BrakeValue", 0.0);
	BlackboardComp->SetValueAsFloat("SteerValue", 0.0);
	BlackboardComp->SetValueAsFloat("ThrottleValue", 0.5);
	
	
}

void AVehicleAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//PrintLog("Inside controller tick ");
}
