// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/GameModeBase.h"

#include "PedestrianSimGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SPAWNPEDESTRIAN_API APedestrianSimGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	APedestrianSimGameModeBase(const FObjectInitializer& ObjectInitializer);

protected:
	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

private:
	void SpawnActorFactories();

	UPROPERTY(Category = "PedSim Game Mode", EditAnywhere)
	TSubclassOf<ACharacter> ThirdPersonCharacterBP;
};
