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
void AWayPoint::calculateCurrentSplineTurnTypes()
{
	float distance = SplineComponent->GetSplineLength();
	directionOfSpline = SplineComponent->GetDirectionAtDistanceAlongSpline(0.0f, ESplineCoordinateSpace::World);
	FVector direction2 = SplineComponent->GetDirectionAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World);
	FVector crossProduct = FVector::CrossProduct(direction2, directionOfSpline);

	if (crossProduct.Z > 0) turnType = "left";
	else if (crossProduct.Z < 0) turnType = "right";
	else if (crossProduct.Z == 0) turnType = "straight";
}

FString AWayPoint::calculateDecalSelection()
{
	if (ConnectedSpline.Num() > 1)
	{
		FString temp = "";
		for (auto i : ConnectedSpline)
		{
			if ((i->turnType).Equals(TEXT("right"))) temp = "straightRight";
			else if ((i->turnType).Equals(TEXT("left"))) temp = "straightLeft";
		}
		return temp;
	}
	else if (ConnectedSpline.Num() == 1) return (ConnectedSpline[0]->turnType);
	else
	{
		FString temp = "";
		return temp;
	}
}

