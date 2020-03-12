// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskChangeSpline.h"
#include "VehicleAIController.h"
#include "WayPoint.h"
#include "Engine.h"

EBTNodeResult::Type UTaskChangeSpline::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	UBehaviorTreeComponent& MyComp = OwnerComp;
	AVehicleAIController* MyController = &MyComp ? Cast<AVehicleAIController>(MyComp.GetOwner()) : NULL;
	if (MyController == NULL)
	{
		return EBTNodeResult::Failed;
	}
	AWayPoint* WayPoint = Cast<AWayPoint>(MyController->BlackboardComponent->GetValueAsObject("WayPoint"));
	int connected_spline_number = WayPoint->ConnectedSpline.Num();
	if (connected_spline_number > 0)
	{
		PrintLog("before remove " + WayPoint->VehiclePawnList.Num());
		RemoveFromWaypoint(WayPoint, MyController);
		PrintLog("After remove " + WayPoint->VehiclePawnList.Num());
		int n = FMath::RandRange(0, connected_spline_number - 1);
		MyController->BlackboardComponent->SetValueAsObject("WayPoint", WayPoint->ConnectedSpline[n]);
		PrintLog("before add " + WayPoint->ConnectedSpline[n]->VehiclePawnList.Num());
		WayPoint->ConnectedSpline[n]->VehiclePawnList.Add(MyController->GetPawn());
		PrintLog("after add " + WayPoint->ConnectedSpline[n]->VehiclePawnList.Num());
		MyController->BlackboardComponent->SetValueAsFloat("DistanceAlongWayPoint", 0.0);
		MyController->BlackboardComponent->SetValueAsBool("IsStopSignAhead", WayPoint->ConnectedSpline[n]->isStopSignConnected);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}

void UTaskChangeSpline::RemoveFromWaypoint(AWayPoint* WayPoint, AVehicleAIController* Controller)
{
	for (APawn* vehicle : WayPoint->VehiclePawnList)
	{
		//AVehicleAIController* controller = vehicle.
		if(vehicle == Controller->GetPawn())
		{
			WayPoint->VehiclePawnList.Remove(vehicle);
		}
		
	}
}


