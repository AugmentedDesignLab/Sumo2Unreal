// Fill out your copyright notice in the Description page of Project Settings.

#include "EdgeMesh.h"
#include "ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"
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
	UE_LOG(LogTemp, Warning, TEXT("*** Constructor of AEdgeMesh ***"));
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	/*
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialO(TEXT(""));
	if (MaterialO.Object != NULL)
	{
		Material = (UMaterial*)MaterialO.Object;
	}
	*/
	RootComponent = mesh;
	mesh->bUseAsyncCooking = true;
}

AEdgeMesh::~AEdgeMesh()
{}


void AEdgeMesh::CreateFace(int32 indexb)
{
	
	for (int i = 0; i < vertices.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("vertices[%d]: "), i);
		UE_LOG(LogTemp, Warning, TEXT("FVectorX: %f"), vertices[i].X);
		UE_LOG(LogTemp, Warning, TEXT("FVectorY: %f"), vertices[i].Y);
		UE_LOG(LogTemp, Warning, TEXT("FVectorZ: %f"), vertices[i].Z);
		UE_LOG(LogTemp, Warning, TEXT("====="));

		Point vertex;
		vertex[0] = vertices[i].X;
		vertex[1] = vertices[i].Y;
		polygonVertices.push_back(vertex);
	}
	polygon.push_back(polygonVertices);

	std::vector<N> indices = mapbox::earcut<N>(polygon);//3 consecutive indices in clockwise order

	int i = 0;
	while((i+3)<=indices.size())
	{
		Triangles.Add((int32)indices[i + 2]);
		Triangles.Add((int32)indices[i + 1]);
		Triangles.Add((int32)indices[i]);
		i += 3;
	}
	for (int j = 0; j < Triangles.Num(); j++) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Triangles[%d]: %d "), j, Triangles[j]);
		UE_LOG(LogTemp, Warning, TEXT("====="));
	}

	normals.Add(FVector(0, 0, 1));
	normals.Add(FVector(0, 0, 1));
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
	tangents.Add(FProcMeshTangent(0, 1, 0));
	tangents.Add(FProcMeshTangent(0, 1, 0));

	vertexColors.Add(FLinearColor((float)(0), (float)(0), (float)(0), 1));
	vertexColors.Add(FLinearColor((float)(0), (float)(0), (float)(0), 1));
	vertexColors.Add(FLinearColor((float)(0), (float)(0), (float)(0), 1));
	vertexColors.Add(FLinearColor((float)(0), (float)(0), (float)(0), 1));
	vertexColors.Add(FLinearColor((float)(0), (float)(0), (float)(0), 1));
	vertexColors.Add(FLinearColor((float)(0), (float)(0), (float)(0), 1));
	
}

void AEdgeMesh::CreateSection(int32 indexa)
{
	CreateFace(indexa);

	mesh->CreateMeshSection_LinearColor(indexa, vertices, Triangles, normals, UV0, vertexColors, tangents, true);
	//mesh->SetMaterial(0, Material);

	// Enable collision data
	mesh->ContainsPhysicsTriMeshData(true);

	UE_LOG(LogTemp, Warning, TEXT("In CreateSection"));
}


void AEdgeMesh::OnConstruction(const FTransform & Transform)
{
	
	AActor::OnConstruction(Transform);
	UE_LOG(LogTemp, Warning, TEXT("==> In OnConstruction"));
	CreateFace(0);

	mesh->CreateMeshSection_LinearColor(0, vertices, Triangles, normals, UV0, vertexColors, tangents, true);
	//UMaterialInstanceDynamic* MaterialInstance = UMaterialInstanceDynamic::Create(Material, this);
	//mesh->SetMaterial(0, MaterialInstance);
	//Enable collision data
	mesh->ContainsPhysicsTriMeshData(true);
}

void AEdgeMesh::PostInitializeComponents()
{
	AActor::PostInitializeComponents();
	UE_LOG(LogTemp, Warning, TEXT("==> In PostInitializeComponents"));
}



void AEdgeMesh::PostActorCreated()
{
	AActor::PostActorCreated();

	//Reset All Tarrays
	//vertices.Reset(0);
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
	AActor::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("*** BeginPlay of AEdgeMesh ***"));
	//CreateSection(0);

}

// Called every frame
void AEdgeMesh::Tick(float DeltaTime)
{
	AActor::Tick(DeltaTime);

}
