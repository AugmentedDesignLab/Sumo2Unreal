// Fill out your copyright notice in the Description page of Project Settings.

#include "GuidingSpline.h"


// Sets default values
AGuidingSpline::AGuidingSpline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Spline = CreateDefaultSubobject<USplineComponent>("SplineObject");
	RootComponent = Spline;
}

// Called when the game starts or when spawned
void AGuidingSpline::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGuidingSpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

