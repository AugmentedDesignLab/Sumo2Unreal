// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "RoadMesh.h"
#include "ConstructorHelpers.h"
#include "Engine.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceConstant.h"
#include <map>
#include <stack>
#include <iostream>
#include <deque>
#include <algorithm>
#include <iterator>
#include <sstream>

const float pi = std::acos(-1);

// Sets default values
ARoadMesh::ARoadMesh()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	mesh->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	//static const ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> MaterialO(TEXT("MaterialInstanceConstant'/Game/CarlaContent/Static/GenericMaterials/Brick/M_Brick_03.M_Brick_03'"));
	//static ConstructorHelpers::FObjectFinder<UTexture2D> TextureO(TEXT("Texture2D'/Game/CarlaAssets/Static/GenericMaterials/Brick/T_Brick_02_d.T_Brick_02_d'"));
	//TArray<UTexture*> textureArray;
	//textureArray.Add((UTexture*)TextureO.Object);

	/*
	if (MaterialO.Succeeded())
	{
		Material = (UMaterial*)MaterialO.Object;
		//UMaterialInstanceDynamic* MaterialInstance = UMaterialInstanceDynamic::Create(Material, this);
		mesh->SetMaterial(0, Material);
	}
	mesh->bUseAsyncCooking = true;
	*/

	eachTriangleNormal.Init(FVector(0.0f, 0.0f, 1.0f), 3);
	eachTriangleTangents.Init(FProcMeshTangent(1.0f, 0.0f, 0.0f), 3);
	eachTriangleVertexColors.Init(FLinearColor(0.0f, 0.0f, 0.0f, 1.0f), 3);
}

ARoadMesh::~ARoadMesh()
{}


void ARoadMesh::CreateSection()
{
	TArray<float> vertexXCoordinates;
	vertexXCoordinates.Empty();
	TArray<float> vertexYCoordinates;
	vertexYCoordinates.Empty();
	for (int i = 0; i < vertices.Num(); i++)
	{
		Point vertex;
		vertex[0] = vertices[i].X;
		vertex[1] = vertices[i].Y; 
		vertexXCoordinates.Add(vertices[i].X);
		UE_LOG(LogEngine, Warning, TEXT("-=-=-=-=-=-=-=-= VERTEX X COORDINATE IS %f -=-=-=-="), vertices[i].X);
		vertexYCoordinates.Add(vertices[i].Y);
		UE_LOG(LogEngine, Warning, TEXT("-=-=-=-=-=-=-=-= VERTEX Y COORDINATE IS %f -=-=-=-="), vertices[i].Y);
		polygonVertices.push_back(vertex);
	}
	polygon.push_back(polygonVertices);
	std::vector<N> indices = mapbox::earcut<N>(polygon);
	//3 consecutive indices in clockwise order of the vertices of the input polygon.

	int i = 0;
	//creating triangles from these indices. Each iteration is a new triangle.
	while ((i + 3) <= indices.size())
	{
		Triangles.Add((uint32_t)indices[i+2]); //assuming that the first triangle starts from 0
		Triangles.Add((uint32_t)indices[i+1]);
		Triangles.Add((uint32_t)indices[i]);
		normals.Append(eachTriangleNormal);
		tangents.Append(eachTriangleTangents);
		vertexColors.Append(eachTriangleVertexColors);
		i += 3;
	}

	/*
	if (vertices.Num() == 4) {
		UV0.Add(FVector2D(0.0f, (roadLength*2)));
		UV0.Add(FVector2D(6.40f, (roadLength * 2)));
		UV0.Add(FVector2D(6.40f, 0.0f));
		UV0.Add(FVector2D(0.0f, 0.0f));
	}
	else {
		/*
	UV mapping calculation - We need to map the 2D texture surface to the 2D junction surface.
	We need to find the Xmax, Xmin, Ymax and Ymin of the polygon. Then we calculate Xrange and Yrange of the polygon.
	After normalizing the coordinates of the vertices over this range, we can make the polygon fit over the 2D texture.
	*/
	float Xrange = FMath::Max(vertexXCoordinates) - FMath::Min(vertexXCoordinates);
	UE_LOG(LogEngine, Warning, TEXT("-=-=-=-=-=-=-=-= VERTEX Xrange IS %f -=-=-=-="), Xrange);
	float Yrange = FMath::Max(vertexYCoordinates) - FMath::Min(vertexYCoordinates);
	UE_LOG(LogEngine, Warning, TEXT("-=-=-=-=-=-=-=-= VERTEX Yrange IS %f -=-=-=-="), Yrange);

		
	float minimumX = FMath::Min(vertexXCoordinates);
	float minimumY = FMath::Min(vertexYCoordinates);
	for (int32 i = 0; i < vertices.Num(); i++) {
		float X = (vertices[i].X - minimumX) / 50.0f;
		float Y = (vertices[i].Y - minimumY) / 50.0f;
		UE_LOG(LogEngine, Warning, TEXT("-=-=-=-=-=-=-=-= NORMALIZED VERTEX X COORDINATE IS %d -=-=-=-="), X);
		UE_LOG(LogEngine, Warning, TEXT("-=-=-=-=-=-=-=-= NORMALIZED VERTEX Y COORDINATE IS %d -=-=-=-="), Y);
		UV0.Add(FVector2D(X, Y));
	}
	vertexXCoordinates.Empty();
	vertexYCoordinates.Empty();
}



void ARoadMesh::OnConstruction(const FTransform & Transform)
{
	AActor::OnConstruction(Transform);
	CreateSection();
	mesh->CreateMeshSection_LinearColor(0, vertices, Triangles, normals, UV0, vertexColors, tangents, false);
	mesh->ContainsPhysicsTriMeshData(true); //Enable collision data
}

void ARoadMesh::PostInitializeComponents()
{
	AActor::PostInitializeComponents();
}

void ARoadMesh::PostActorCreated()
{
	AActor::PostActorCreated();
}

void ARoadMesh::PostLoad()
{
	AActor::PostLoad();
	vertices.Empty();
	Triangles.Empty();
	UV0.Empty();
	normals.Empty();
	vertexColors.Empty();
	tangents.Empty();
}

// Called when the game starts or when spawned
void ARoadMesh::BeginPlay()
{
	AActor::BeginPlay();
}

// Called every frame
void ARoadMesh::Tick(float DeltaTime)
{
	AActor::Tick(DeltaTime);
}
