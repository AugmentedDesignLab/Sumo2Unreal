// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "PedestrianAIController.generated.h"

UCLASS()
class SPAWNPEDESTRIAN_API APedestrianAIController : public AAIController
{
	GENERATED_BODY()

protected:

	UPROPERTY(Transient)
	UBehaviorTreeComponent* BehaviorComp;

	UPROPERTY(Transient)
	UBlackboardComponent* BlackboardComp;

public:
	APedestrianAIController();

	void OnPossess(APawn* InPawn) override;

	// Key Id for "TargetLocation" FVector
	// 
	uint8 TargetKeyId;
};
