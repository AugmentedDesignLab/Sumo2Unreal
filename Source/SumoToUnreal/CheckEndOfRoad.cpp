// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckEndOfRoad.h"
#include "VehicleAIController.h"
#include "WheeledVehicleObject.h"

EBTNodeResult::Type UCheckEndOfRoad::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBehaviorTreeComponent& MyComp = OwnerComp;
	AVehicleAIController* MyController = &MyComp ? Cast<AVehicleAIController>(MyComp.GetOwner()) : NULL;
	if (MyController == NULL)
	{
		return EBTNodeResult::Failed;
	}
	AWayPoint* WayPoint = Cast<AWayPoint>(MyController->BlackboardComponent->GetValueAsObject("WayPoint"));
	if(WayPoint->ConnectedSpline.Num() == 0)
	{
		PrintLog(" self destruct... ");
		AWheeledVehicleObject* VehicleObject = Cast<AWheeledVehicleObject>(MyController->BlackboardComponent->GetValueAsObject("VehicleObject"));
		VehicleObject->SelfDestroy();
	}
	
	return EBTNodeResult::Succeeded;
}
