// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "PedestrianAIController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BTTask_MoveToLocation.generated.h"

/**
 * 
 */
UCLASS()
class SPAWNPEDESTRIAN_API UBTTask_MoveToLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

inline EBTNodeResult::Type UBTTask_MoveToLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APedestrianAIController* AI = Cast<APedestrianAIController>(OwnerComp.GetAIOwner());

	FVector TargetLocation = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Vector>(AI->TargetKeyId);

	AI->MoveToLocation(TargetLocation, 5.0f, true, true, true, true, nullptr, true);

	return EBTNodeResult::Succeeded;
}
