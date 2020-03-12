// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomLocation.h"

#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Engine/Engine.h"
#include "NavigationSystem.h"
#include "PedestrianAIController.h"
#include "PedestrianCharacter.h"

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	APedestrianCharacter* OwnerActor = Cast<APedestrianCharacter>(OwnerComp.GetAIOwner()->GetCharacter());
	if (OwnerActor == nullptr) return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetNavigationSystem(OwnerActor->GetWorld());
	if (nullptr == NavSys) return EBTNodeResult::Failed;

	// Find a random location
	// 
	const FVector Origin = OwnerActor->GetActorLocation();
	const float Radius = 1024.0f * 2;
	FNavLocation NewLocation;
	if (NavSys->GetRandomPointInNavigableRadius(Origin, Radius, NewLocation))
	{
		APedestrianAIController* AI = Cast<APedestrianAIController>(OwnerComp.GetAIOwner());

		// Set the value into blackboard.
		OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(AI->TargetKeyId, NewLocation.Location);

		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow,
		                                 "UBTTask_FindRandomLocation::ExecuteTask -- GetRandomPointInNavigableRadius -- OK");
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
