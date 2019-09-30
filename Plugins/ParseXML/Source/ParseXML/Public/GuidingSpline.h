// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Classes/Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "GuidingSpline.generated.h"

UCLASS()
class PARSEXML_API AGuidingSpline : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGuidingSpline();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	USplineComponent *Spline;
	UPROPERTY(EditAnywhere)
	FString splineID;
	UPROPERTY(EditAnywhere)
	TArray<AGuidingSpline*> NextSplineActorList;
};


