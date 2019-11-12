// Fill out your copyright notice in the Description page of Project Settings.

#include "StopSignMesh.h"
#include "EngineMinimal.h"


// Sets default values
AStopSignMesh::AStopSignMesh()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	stopSignMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("stopSignActor"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>stopSignMeshAsset(TEXT("StaticMesh'/Game/finalStopSign/StopSignStaticMesh3.StopSignStaticMesh3'"));
	UStaticMesh* stopSignMesh= stopSignMeshAsset.Object;
	stopSignMeshComponent->SetStaticMesh(stopSignMesh);
}

// Called when the game starts or when spawned
void AStopSignMesh::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStopSignMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

