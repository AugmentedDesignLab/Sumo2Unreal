// Fill out your copyright notice in the Description page of Project Settings.


#include "StopCar.h"
#include "VehicleController.h"
#include "Engine.h"

EBTNodeResult::Type UStopCar::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//PrintLog(OwnerComp.GetName());
	FVector stop_location;
	UBehaviorTreeComponent& MyComp = OwnerComp;
	stop_location = MyComp.GetBlackboardComponent()->GetValueAsVector("StopSign");
	
	//PrintLog(" StopLoc " + stop_location.ToString());
	AVehicleController* MyController = &MyComp ? Cast<AVehicleController>(MyComp.GetOwner()) : NULL;
	if (MyController == NULL)
	{
		return EBTNodeResult::Failed;
	}
	float distance = FVector::Distance(stop_location, MyController->Vehicle->GetVehicleLocation());

	//PrintLog("Distance " + FString::SanitizeFloat(distance));
	if (distance < 1000)
	{
		MyComp.GetBlackboardComponent()->SetValueAsBool("IsNormalRoad", false);
		if(MyController->StopSignLocation.Num()>= 1)
		{ 
			MyController->StopSignLocation.Remove(stop_location);
			return EBTNodeResult::Succeeded;
		}
			
	}

	return EBTNodeResult::Failed;
}

void UStopCar::PrintLog(FString Text)
{
	if (!GEngine) return;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, *Text);
}
