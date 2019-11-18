// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskStopAtStopSign.h"
#include "VehicleAIController.h"
#include "WheeledVehicleObject.h"
#include "Kismet/KismetSystemLibrary.h"

EBTNodeResult::Type UTaskStopAtStopSign::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBehaviorTreeComponent& MyComp = OwnerComp;
	AVehicleAIController* MyController = &MyComp ? Cast<AVehicleAIController>(MyComp.GetOwner()) : NULL;
	if (MyController == NULL)
	{
		return EBTNodeResult::Failed;
	}
	AWheeledVehicleObject* VehicleObject = Cast<AWheeledVehicleObject>(MyController->BlackboardComp->GetValueAsObject("VehicleObject"));
	if (VehicleObject->GetVelocity().Size() > 0)
	{
		float BrakeValue = MyController->BlackboardComp->GetValueAsFloat("BrakeValue");
		if (BrakeValue < 1) 
		{
			BrakeValue += 0.1;
		}
		MyController->BlackboardComp->SetValueAsFloat("BrakeValue", BrakeValue);
		MyController->BlackboardComp->SetValueAsFloat("ThrottleValue", 0.0);
		StartTime = UKismetSystemLibrary::GetGameTimeInSeconds(this);
		//PrintLog("Start time " + FString::SanitizeFloat(StartTime));
		return EBTNodeResult::Failed;

	}
	else
	{
		if (UKismetSystemLibrary::GetGameTimeInSeconds(this) - StartTime < 3.0)
		{
			return EBTNodeResult::Failed;
		}
		else
		{
			MyController->BlackboardComp->SetValueAsBool("IsStopSignAhead", false);
			MyController->BlackboardComp->SetValueAsFloat("BrakeValue", 0.0);
			MyController->BlackboardComp->SetValueAsFloat("ThrottleValue", 0.5);
			return EBTNodeResult::Succeeded;
		}
	}

}
