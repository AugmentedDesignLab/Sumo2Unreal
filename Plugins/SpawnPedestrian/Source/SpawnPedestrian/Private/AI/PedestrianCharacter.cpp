// Fill out your copyright notice in the Description page of Project Settings.


#include "PedestrianCharacter.h"

// Sets default values
APedestrianCharacter::APedestrianCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APedestrianCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APedestrianCharacter::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APedestrianCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
