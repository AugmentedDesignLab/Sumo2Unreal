// Fill out your copyright notice in the Description page of Project Settings.


#include "PedestrianAIController.h"
#include "PedestrianCharacter.h"
#include "Engine/Engine.h"

APedestrianAIController::APedestrianAIController()
{
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void APedestrianAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, "APedestrianAIController::OnPossess");

	APedestrianCharacter* Pedestrian = Cast<APedestrianCharacter>(InPawn);

	if (Pedestrian && Pedestrian->BehaviorTree)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green,
		                                 "APedestrianAIController::OnPossess --- AI && AI->BehaviorTree");

		BlackboardComp->InitializeBlackboard(*Pedestrian->BehaviorTree->BlackboardAsset);

		TargetKeyId = BlackboardComp->GetKeyID("TargetLocation");

		BehaviorComp->StartTree(*Pedestrian->BehaviorTree);
	}
}
