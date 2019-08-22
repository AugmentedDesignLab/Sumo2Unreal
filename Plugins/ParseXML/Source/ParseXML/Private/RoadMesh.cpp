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
	static const ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> MaterialO(TEXT("MaterialInstanceConstant'/Game/CarlaContent/Static/GenericMaterials/Brick/M_Brick_03.M_Brick_03'"));
	//static ConstructorHelpers::FObjectFinder<UTexture2D> TextureO(TEXT("Texture2D'/Game/CarlaAssets/Static/GenericMaterials/Brick/T_Brick_02_d.T_Brick_02_d'"));
	//TArray<UTexture*> textureArray;
	//textureArray.Add((UTexture*)TextureO.Object);

	if (MaterialO.Succeeded())
	{
		Material = (UMaterial*)MaterialO.Object;
		//UMaterialInstanceDynamic* MaterialInstance = UMaterialInstanceDynamic::Create(Material, this);
		mesh->SetMaterial(0, Material);
	}
	mesh->bUseAsyncCooking = true;

	eachTriangleNormal.Init(FVector(0.0f, 0.0f, 1.0f), 3);
	eachTriangleTangents.Init(FProcMeshTangent(1.0f, 0.0f, 0.0f), 3);
	eachTriangleVertexColors.Init(FLinearColor(0.0f, 0.0f, 0.0f, 1.0f), 3);
}

ARoadMesh::~ARoadMesh()
{}


void ARoadMesh::CreateSection()
{
	for (int i = 0; i < vertices.Num(); i++)
	{
		Point vertex;
		vertex[0] = vertices[i].X;
		vertex[1] = vertices[i].Y; //create a mirror of the network about the x-axis.
		UE_LOG(LogEngine, Warning, TEXT("________________The vertex coordinates are (%f, %f)___________"), vertex[0], vertex[1]);
		polygonVertices.push_back(vertex);
	}
	polygon.push_back(polygonVertices);
	std::vector<N> indices = mapbox::earcut<N>(polygon);//3 consecutive indices in clockwise order

	int i = 0;
	//creating triangles from these indices. Each iteration is a new triangle.
	while ((i + 3) <= indices.size())
	{
		UE_LOG(LogEngine, Warning, TEXT("________________The index coordinates are (%d, %d, %d)___________"), (uint32_t)indices[i], (uint32_t)indices[i+1], (uint32_t)indices[i+2]);
		Triangles.Add((uint32_t)indices[i+2]);
		Triangles.Add((uint32_t)indices[i+1]);
		Triangles.Add((uint32_t)indices[i]);
		normals.Append(eachTriangleNormal);
		tangents.Append(eachTriangleTangents);
		vertexColors.Append(eachTriangleVertexColors);
		i += 3;
	}
	UV0.Add(FVector2D(0.0f, 0.0f));
	UV0.Add(FVector2D(1.0f, 0.0f));
	UV0.Add(FVector2D(0.0f, 1.0f));
	UV0.Add(FVector2D(1.0f, 1.0f));
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
