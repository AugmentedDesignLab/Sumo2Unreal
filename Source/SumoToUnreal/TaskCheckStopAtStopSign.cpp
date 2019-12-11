// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskCheckStopAtStopSign.h"
#include "VehicleAIController.h"

EBTNodeResult::Type UTaskCheckStopAtStopSign::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//ThreshStopAtStopSignDistance

	UBehaviorTreeComponent& MyComp = OwnerComp;
	AVehicleAIController* MyController = &MyComp ? Cast<AVehicleAIController>(MyComp.GetOwner()) : NULL;
	if (MyController == NULL)
	{
		return EBTNodeResult::Failed;
	}
	float ThreshStopAtStopSignDistance = MyController->BlackboardComp->GetValueAsFloat("ThreshStopAtStopSignDistance");
	float DistanceAlongWayPoint = MyController->BlackboardComp->GetValueAsFloat("DistanceAlongWayPoint");
	AWayPoint* WayPoint = Cast<AWayPoint>(MyController->BlackboardComp->GetValueAsObject("WayPoint"));
	float SplineLength = WayPoint->SplineComponent->GetSplineLength();
	bool IsStopSignAhead = MyController->BlackboardComp->GetValueAsBool("IsStopSignAhead");
	if ( IsStopSignAhead && (SplineLength - DistanceAlongWayPoint) < ThreshStopAtStopSignDistance) 
	{
		
		return EBTNodeResult::Succeeded;
	}
	else 
	{
		return EBTNodeResult::Failed;
	}

}
