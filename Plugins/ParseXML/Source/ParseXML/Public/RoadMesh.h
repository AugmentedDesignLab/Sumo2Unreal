// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "earcut/earcut.h"
#include <array>
#include "RoadMesh.generated.h"

UENUM()
enum class MeshType
{
	Junction UMETA(DisplayName = "Junction"),
	Sidewalk UMETA(DisplayName = "Sidewalk"),
	Crossing UMETA(DisplayName = "Crossing"),
	Road UMETA(DisplayName = "Road")
};

UCLASS()
class PARSEXML_API ARoadMesh : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	ARoadMesh();
	~ARoadMesh();
	
	UPROPERTY(EditAnywhere, Category = Enum)
	MeshType currentMeshType;

	UPROPERTY(VisibleAnywhere, Category = ProcMesh)
	UMaterial* Material0;

	UPROPERTY(VisibleAnywhere, Category = ProcMesh)
	UMaterial* Material1;

	UPROPERTY(EditAnywhere, Category = ProcMesh)
	UProceduralMeshComponent *mesh;

	UPROPERTY(NonPIEDuplicateTransient) //To make sure that the vertices also get copied for every PIE instance (No loss of actor data)
	TArray<FVector> vertices;
	
	TArray<int32> Triangles;
	TArray<FVector> normals;
	TArray<FVector2D> UV0;
	TArray<FProcMeshTangent> tangents;
	TArray<FLinearColor> vertexColors;
	FString MaterialPath = "";

	//temp triangle arrays
	TArray<FVector> eachTriangleNormal;
	TArray<FProcMeshTangent> eachTriangleTangents;
	TArray<FLinearColor> eachTriangleVertexColors;

	float roadLength;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	using Coord = double;
	using N = uint32_t;
	using Point = std::array<Coord, 2>;

	std::vector<std::vector<Point>> polygon;
	std::vector<Point> polygonVertices;
	
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostActorCreated() override;
	virtual void PostLoad() override;
	virtual void OnConstruction(const FTransform & Transform) override;
	virtual void PostInitializeComponents() override;

	void CreateSection();
};
