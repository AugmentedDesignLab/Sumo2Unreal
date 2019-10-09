// Fill out your copyright notice in the Description page of Project Settings.

#include "WayPoint.h"


// Sets default values
AWayPoint::AWayPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>("SplineObject");
	RootComponent = SplineComponent;
}

// Called when the game starts or when spawned
void AWayPoint::BeginPlay()
{
	Super::BeginPlay();
	TotalDistance = SplineComponent->GetSplineLength();
}

// Called every frame
void AWayPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

