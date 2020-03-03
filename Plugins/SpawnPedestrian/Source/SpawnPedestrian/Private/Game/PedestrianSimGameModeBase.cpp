// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/PedestrianSimGameModeBase.h"
#include "Engine/World.h"
#include "ConstructorHelpers.h"
#include "Engine/Engine.h"

APedestrianSimGameModeBase::APedestrianSimGameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Ivan's note:
	// Refer to this note http://www.programmersought.com/article/2613418406/
	// I am not sure why must we add a trailing _C at the end, otherwise it does not find this object.
	static ConstructorHelpers::FObjectFinder<UClass> PedestrianCharacterAssets(
		TEXT("Blueprint'/SpawnPedestrian/BasePedestrian/Blueprints/BP_PedestrianCharacter.BP_PedestrianCharacter_C'"));

	if (PedestrianCharacterAssets.Succeeded())
	{
		ThirdPersonCharacterBP = PedestrianCharacterAssets.Object;
	}
}

void APedestrianSimGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	FVector Location{-1770.0, 2510.0, 98.0};

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "APedestrianSimGameModeBase::InitGame");

	GetWorld()->SpawnActor<ACharacter>(ThirdPersonCharacterBP, Location, FRotator::ZeroRotator);
}
