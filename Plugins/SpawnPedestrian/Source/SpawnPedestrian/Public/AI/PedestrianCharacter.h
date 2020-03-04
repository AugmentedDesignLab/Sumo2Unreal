// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"
#include "PedestrianCharacter.generated.h"

UCLASS()
class SPAWNPEDESTRIAN_API APedestrianCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APedestrianCharacter();

	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree* BehaviorTree;

protected:
	void BeginPlay() override;

public:
	void Tick(float DeltaTime) override;

	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
