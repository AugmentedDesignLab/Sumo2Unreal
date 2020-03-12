// Fill out your copyright notice in the Description page of Project Settings.
// debug color Blue
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Engine/Engine.h"
#include "CheckEndOfRoad.generated.h"


/**
 * 
 */
UCLASS()
class SUMOTOUNREAL_API UCheckEndOfRoad : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	/*
	* checks if the vehicle reached at the (Length - Threshold) of the spline.
	*/

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void PrintLog(FString Text)
	{
		if (!GEngine) return;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, *Text);
	}
	
};
