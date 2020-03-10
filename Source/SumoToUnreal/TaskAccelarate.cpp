// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskAccelarate.h"
#include "VehicleAIController.h"

EBTNodeResult::Type UTaskAccelarate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBehaviorTreeComponent& MyComp = OwnerComp;
	AVehicleAIController* MyController = &MyComp ? Cast<AVehicleAIController>(MyComp.GetOwner()) : NULL;
	if (MyController == NULL)
	{
		return EBTNodeResult::Failed;
	}
	MyController->BlackboardComponent->SetValueAsBool("IsStopSignAhead", false);
	MyController->BlackboardComponent->SetValueAsFloat("BrakeValue", 0.0);
	MyController->BlackboardComponent->SetValueAsFloat("ThrottleValue", 0.5);
	PrintLog("Accelarating....");
	return EBTNodeResult::Succeeded;
}
