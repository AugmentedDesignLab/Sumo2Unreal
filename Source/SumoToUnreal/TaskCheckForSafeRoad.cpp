// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskCheckForSafeRoad.h"
#include "VehicleAIController.h"
#include "WayPoint.h"

EBTNodeResult::Type UTaskCheckForSafeRoad::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBehaviorTreeComponent& MyComp = OwnerComp;
	AVehicleAIController* MyController = &MyComp ? Cast<AVehicleAIController>(MyComp.GetOwner()) : NULL;
	if (MyController == NULL)
	{
		return EBTNodeResult::Failed;
	}
	AWayPoint* WayPoint = Cast<AWayPoint>(MyController->BlackboardComponent->GetValueAsObject("WayPoint"));
	PrintLog("Number of connected spline " + FString::FromInt(WayPoint->ConnectedSpline.Num()));
	for (AWayPoint* ConnectedSpline : WayPoint->ConnectedSpline)
	{
		PrintLog("Number of cut spline " + FString::FromInt(ConnectedSpline->CutSpline.Num()));
		for (AWayPoint* w : ConnectedSpline->CutSpline)
		{
			if (w->VehiclePawnList.Num() > 0)
			{
				PrintLog("Not safe ");
				return EBTNodeResult::Failed;
			}
		}
	}
	
	PrintLog("Safe ");
	return EBTNodeResult::Succeeded;
}
