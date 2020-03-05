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
	AWheeledVehicleObject* VehicleObject = Cast<AWheeledVehicleObject>(MyController->BlackboardComponent->GetValueAsObject("VehicleObject"));
	FVector2D v = FVector2D(VehicleObject->GetVelocity().X, VehicleObject->GetVelocity().Y);
	if (v.Size() > 1)
	{
		//PrintLog("vehicle velocity " + VehicleObject->GetVelocity().ToString());
		float BrakeValue = MyController->BlackboardComponent->GetValueAsFloat("BrakeValue");
		if (BrakeValue < 1) 
		{
			BrakeValue += 0.1;
		}
		MyController->BlackboardComponent->SetValueAsFloat("BrakeValue", BrakeValue);
		MyController->BlackboardComponent->SetValueAsFloat("ThrottleValue", 0.0);
		StartTime = UKismetSystemLibrary::GetGameTimeInSeconds(this);
		//PrintLog("Start time " + FString::SanitizeFloat(StartTime));
		return EBTNodeResult::Failed;

	}
	else
	{
		if (UKismetSystemLibrary::GetGameTimeInSeconds(this) - StartTime < 1.0)
		{
			//PrintLog("Not time" + FString::SanitizeFloat(UKismetSystemLibrary::GetGameTimeInSeconds(this) - StartTime));
			return EBTNodeResult::Failed;
		}
		else
		{
			//PrintLog("Here we start again");
			MyController->BlackboardComponent->SetValueAsBool("IsStopSignAhead", false);
			MyController->BlackboardComponent->SetValueAsFloat("BrakeValue", 0.0);
			MyController->BlackboardComponent->SetValueAsFloat("ThrottleValue", 0.5);
			return EBTNodeResult::Succeeded;
		}
	}

}
