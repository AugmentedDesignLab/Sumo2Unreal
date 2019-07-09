// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicVehicle.h"

ABasicVehicle::ABasicVehicle()
{
   PrimaryActorTick.bCanEverTick = true;
}

void ABasicVehicle::BeginPlay()
{
   Super::BeginPlay();
}

void ABasicVehicle::Tick(float DeltaTime)
{
   Super::Tick(DeltaTime);
}
