// Fill out your copyright notice in the Description page of Project Settings.

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Classes/Components/SplineComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "WayPoint.generated.h"

UCLASS()
class SUMOTOUNREAL_API AWayPoint : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWayPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	/*
		Variables
	*/

	//main spline component 
	UPROPERTY(EditAnywhere)
	USplineComponent *SP;

	//connected spline with the main spline
	UPROPERTY(EditAnywhere)
	TArray<AWayPoint*> ConnectedSpline;

	//Unique ID for each spline
	UPROPERTY(EditAnywhere)
	int ID = 0;

	//speed limit for this spline
	UPROPERTY(EditAnywhere)
	int SpeedLimit = 0;

	//total distance of this spline
	float TotalDistance = 0.0;

};
