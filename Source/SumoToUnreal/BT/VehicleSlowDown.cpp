// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleSlowDown.h"
#include "VehicleController.h"
#include "Engine.h"

EBTNodeResult::Type UVehicleSlowDown::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBehaviorTreeComponent& MyComp = OwnerComp;
	AVehicleController* MyController = &MyComp ? Cast<AVehicleController>(MyComp.GetOwner()) : NULL;
	if (MyController == NULL)
	{
		return EBTNodeResult::Failed;
	}
	
	float distance = FVector::Distance( MyController->Vehicle->GetVehicleLocation(), MyController->OtherVehicleOnSpline->GetVehicleLocation());
	if (distance < DistanceThreshold) 
	{
		//PrintLog("Inside Vehicle Slow Down");
		MyComp.GetBlackboardComponent()->SetValueAsBool("IsNormalRoad", false);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		MyComp.GetBlackboardComponent()->SetValueAsBool("IsNormalRoad", true);
		return EBTNodeResult::Failed;
	}
}

void UVehicleSlowDown::PrintLog(FString Text)
{
	if (!GEngine) return;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, *Text);
}
