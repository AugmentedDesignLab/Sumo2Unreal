// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"
#include "PedestrianAIController.h"
#include "PedestrianCharacter.generated.h"

UCLASS()
class SPAWNPEDESTRIAN_API APedestrianCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APedestrianCharacter();

	// We are attaching a behavior tree component to the pedestrian character
	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree* BehaviorTree;

protected:
	void BeginPlay() override;

public:
	void Tick(float DeltaTime) override;

	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
