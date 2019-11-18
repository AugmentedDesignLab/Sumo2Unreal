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

	AWayPoint* WayPoint = Cast<AWayPoint>(MyController->BlackboardComp->GetValueAsObject("WayPoint"));
	int connected_spline_number = WayPoint->ConnectedSpline.Num();
	if (connected_spline_number > 0)
	{
		int n = FMath::RandRange(0, connected_spline_number - 1);
		MyController->BlackboardComp->SetValueAsObject("WayPoint", WayPoint->ConnectedSpline[n]);
		MyController->BlackboardComp->SetValueAsFloat("DistanceAlongWayPoint", 0.0);
		MyController->BlackboardComp->SetValueAsBool("IsStopSignAhead", WayPoint->ConnectedSpline[n]->isStopSignConnected);
		//PrintLog("Is there stop sign " + WayPoint->ConnectedSpline[n]->isStopSignConnected);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}


