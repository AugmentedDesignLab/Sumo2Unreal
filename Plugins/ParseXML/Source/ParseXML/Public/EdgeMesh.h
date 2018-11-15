// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "EdgeMesh.generated.h"

UCLASS()
class PARSEXML_API AEdgeMesh : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEdgeMesh();

	UProceduralMeshComponent *mesh;
	UPROPERTY(NonPIEDuplicateTransient)
	TArray<FVector> vertices;
	
	TArray<int32> Triangles;
	TArray<FVector> normals;
	TArray<FVector2D> UV0;
	TArray<FProcMeshTangent> tangents;
	TArray<FLinearColor> vertexColors;

	FVector vertex1;
	FVector vertex2;
	FVector vertex3;
	FVector vertex4;

	int32 returnEdge;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostActorCreated() override;
	virtual void PostLoad() override;
	virtual void OnConstruction(const FTransform & Transform) override;
	virtual void PostInitializeComponents() override;

	void CreateFace(int32);
	void CreateSection(int32);
};
