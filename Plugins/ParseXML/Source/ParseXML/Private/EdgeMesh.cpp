// Fill out your copyright notice in the Description page of Project Settings.

#include "EdgeMesh.h"
#include <map>
#include <stack>
#include <iostream>
#include <deque>
#include <algorithm>
#include <iterator>
#include <sstream>

const float pi = std::acos(-1);

// Sets default values
AEdgeMesh::AEdgeMesh()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	RootComponent = mesh;
	mesh->bUseAsyncCooking = true;
}


void AEdgeMesh::CreateFace(FVector vertex1b, FVector vertex2b, FVector vertex3b, FVector vertex4b, int32 indexb)
{
	
	Triangles.Add(0);
	Triangles.Add(3);
	Triangles.Add(1);

	Triangles.Add(1);
	Triangles.Add(3);
	Triangles.Add(2);


	normals.Add(FVector(0, 0, 1));
	normals.Add(FVector(0, 0, 1));
	normals.Add(FVector(0, 0, 1));
	normals.Add(FVector(0, 0, 1));

	UV0.Add(FVector2D(0, 0));
	UV0.Add(FVector2D(1, 0));
	UV0.Add(FVector2D(0, 1));

	tangents.Add(FProcMeshTangent(0, 1, 0));
	tangents.Add(FProcMeshTangent(0, 1, 0));
	tangents.Add(FProcMeshTangent(0, 1, 0));
	tangents.Add(FProcMeshTangent(0, 1, 0));

	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));

}

void AEdgeMesh::CreateSection(FVector vertex1a, FVector vertex2a, FVector vertex3a, FVector vertex4a, int32 indexa)
{
	CreateFace(vertex1a, vertex2a, vertex3a, vertex4a, indexa);

	mesh->CreateMeshSection_LinearColor(indexa, vertices, Triangles, normals, UV0, vertexColors, tangents, true);

	// Enable collision data
	mesh->ContainsPhysicsTriMeshData(true);

	UE_LOG(LogTemp, Warning, TEXT("In CreateSection"));
}


void AEdgeMesh::PostActorCreated()
{
	AActor::PostActorCreated();

	//Reset All Tarrays
	vertices.Reset(0);
	Triangles.Reset(0);
	normals.Reset(0);
	UV0.Reset(0);
	tangents.Reset(0);
	vertexColors.Reset(0);

}

void AEdgeMesh::PostLoad()
{
	AActor::PostLoad();
}

// Called when the game starts or when spawned
void AEdgeMesh::BeginPlay()
{
	CreateSection(vertex1, vertex2, vertex3, vertex4, 0);
	AActor::BeginPlay();

}

// Called every frame
void AEdgeMesh::Tick(float DeltaTime)
{
	AActor::Tick(DeltaTime);

}
