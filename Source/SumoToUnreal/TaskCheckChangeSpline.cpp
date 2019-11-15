// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskCheckChangeSpline.h"
#include "VehicleAIController.h"
#include "WayPoint.h"
#include "Engine.h"

EBTNodeResult::Type UTaskCheckChangeSpline::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	UBehaviorTreeComponent& MyComp = OwnerComp;
	AVehicleAIController* MyController = &MyComp ? Cast<AVehicleAIController>(MyComp.GetOwner()) : NULL;
	if (MyController == NULL)
	{
		return EBTNodeResult::Failed;
	}

	AWayPoint* WayPoint = Cast<AWayPoint>(MyController->BlackboardComp->GetValueAsObject("WayPoint"));
	float TotalWayPointLength = WayPoint->TotalDistance;
	float DistanceAlongWayPoint = MyController->DistanceAlongWayPoint;

	if (TotalWayPointLength - DistanceAlongWayPoint < SplineChangeThreshold)
	{
		PrintLog("Success from the check task change spline");
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}

void UTaskCheckChangeSpline::PrintLog(FString Text)
{
	if (!GEngine) return;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, *Text);
}
