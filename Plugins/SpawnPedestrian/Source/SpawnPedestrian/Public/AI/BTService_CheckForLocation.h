// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CheckForLocation.generated.h"

/**
 * 
 */
UCLASS()
class SPAWNPEDESTRIAN_API UBTService_CheckForLocation : public UBTService
{
	GENERATED_BODY()

public:

	UBTService_CheckForLocation() { bCreateNodeInstance = true; }

	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
