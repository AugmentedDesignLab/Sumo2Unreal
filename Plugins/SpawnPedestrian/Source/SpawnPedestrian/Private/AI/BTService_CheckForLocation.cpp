// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckForLocation.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "AI/PedestrianAIController.h"

void UBTService_CheckForLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	APedestrianAIController* AI = Cast<APedestrianAIController>(OwnerComp.GetAIOwner());

	if (AI)
	{
		// TODO: Make this a new random position
		const FVector NewLocation = FVector::ZeroVector;

		OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(AI->TargetKeyId, NewLocation);
	}
}
