// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeStopSignLocation.h"
#include "VehicleController.h"
#include "Engine.h"

EBTNodeResult::Type UChangeStopSignLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBehaviorTreeComponent& MyComp = OwnerComp;
	AVehicleController* MyController = &MyComp ? Cast<AVehicleController>(MyComp.GetOwner()) : NULL;
	if (MyController == NULL)
	{
		return EBTNodeResult::Failed;
	}

	MyComp.GetBlackboardComponent()->SetValueAsBool("IsStopSignAhead", false);
	MyComp.GetBlackboardComponent()->SetValueAsBool("IsNormalRoad", true);
	return EBTNodeResult::Succeeded;

}

void UChangeStopSignLocation::PrintLog(FString Text)
{
	if (!GEngine) return;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, *Text);
}
