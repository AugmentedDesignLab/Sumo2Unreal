// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeSpline.h"
#include "VehicleController.h"
#include "Engine.h"

EBTNodeResult::Type UChangeSpline::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBehaviorTreeComponent& MyComp = OwnerComp;
	AVehicleController* MyController = &MyComp ? Cast<AVehicleController>(MyComp.GetOwner()) : NULL;
	if (MyController == NULL)
	{
		return EBTNodeResult::Failed;
	}
	AWayPoint* temp_waypoint = MyController->Vehicle->GetWayPoint();
	float spline_distance = temp_waypoint->TotalDistance;
	float vehicle_distance = MyController->Vehicle->GetTraveledDistance();
	if (vehicle_distance + SplineChangeThreshold > spline_distance)
	{
		//PrintLog("Inside distance threshold for spline change");
		int connected_spline_number = temp_waypoint->ConnectedSpline.Num();
		if (connected_spline_number > 0)
		{
			int n = FMath::RandRange(0, connected_spline_number - 1);
			MyController->Vehicle->SetWayPoint(temp_waypoint->ConnectedSpline[n]);
			MyController->Vehicle->SetTraveledDistance(0.0);
			MyController->Vehicle->SetSpeedLimit(temp_waypoint->ConnectedSpline[n]->SpeedLimit);
			return EBTNodeResult::Succeeded;
		}
		else
		{
			MyComp.GetBlackboardComponent()->SetValueAsBool("IsNormalRoad", false);
			return EBTNodeResult::Succeeded;
		}
	}


	return EBTNodeResult::Failed;
}

void UChangeSpline::PrintLog(FString Text)
{
	if (!GEngine) return;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, *Text);
}
