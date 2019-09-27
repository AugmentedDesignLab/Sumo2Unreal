// Fill out your copyright notice in the Description page of Project Settings.



#include "VehicleMovement.h"
#include "Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "UnrealMathUtility.h"



AVehicleMovement::AVehicleMovement()
{
	
}

void AVehicleMovement::BeginPlay()
{
	Super::BeginPlay();
}

void AVehicleMovement::PrintLog(FString text)
{
	if (!GEngine) return;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, *text);
}

 FVehicleControl& AVehicleMovement::GetLastControl()
{
	return LastControl;
}

FTransform AVehicleMovement::GetVehicleTransform()
{
	return GetActorTransform();
}

FVector AVehicleMovement::GetVehicleLocation()
{
	return GetActorLocation();
}

FVector AVehicleMovement::GetVehicleForward()
{
	return GetActorForwardVector();
}

FVector AVehicleMovement::GetVehicleVelocity()
{
	return GetVelocity();
}

float AVehicleMovement::GetTraveledDistance()
{
	return LastControl.TraveledDistance;
}

float AVehicleMovement::GetSpeedLimit()
{
	return LastControl.SpeedLimit;
}

AWayPoint* AVehicleMovement::GetWayPoint()
{
	return LastControl.WayPoint;
}

void AVehicleMovement::SetLocation(FVector Location)
{
	this->SetActorLocation(Location);
}

void AVehicleMovement::SetControl()
{
	this->GetVehicleMovement()->SetThrottleInput(LastControl.ThrottleValue);
	this->GetVehicleMovement()->SetSteeringInput(LastControl.SteeringValue);
	this->GetVehicleMovement()->SetBrakeInput(LastControl.BrakeValue);
}

void AVehicleMovement::SetSteeringValue(float SteeringValue)
{
	LastControl.SteeringValue = SteeringValue;
}

void AVehicleMovement::SetThrottleValue(float ThrottleValue)
{
	LastControl.ThrottleValue = ThrottleValue;
}

void AVehicleMovement::SetBrakeValue(float BrakeValue)
{
	LastControl.BrakeValue = BrakeValue;
}

void AVehicleMovement::SetWayPoint(AWayPoint* WayPoint)
{
	LastControl.WayPoint = WayPoint;
}

void AVehicleMovement::SetSpeedLimit(float SpeedLimit)
{
	LastControl.SpeedLimit = SpeedLimit;
}

void AVehicleMovement::SetTraveledDistance(float Distance)
{
	LastControl.TraveledDistance = Distance;
}

void AVehicleMovement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}  