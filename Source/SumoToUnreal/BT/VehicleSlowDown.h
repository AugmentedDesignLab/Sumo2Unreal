// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "VehicleSlowDown.generated.h"

/**
 * 
 */
UCLASS()
class SUMOTOUNREAL_API UVehicleSlowDown : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void PrintLog(FString Text);

	float DistanceThreshold = 1000.0;
};
