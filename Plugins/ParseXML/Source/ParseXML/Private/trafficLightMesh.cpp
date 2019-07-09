// Fill out your copyright notice in the Description page of Project Settings.

#include "trafficLightMesh.h"
#include "EngineMinimal.h"


// Sets default values
AtrafficLightMesh::AtrafficLightMesh()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	trafficLightComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("trafficLightActor"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>trafficLightMeshAsset(TEXT("StaticMesh'/Game/trafficlight/traffic_signal.traffic_signal'"));
	UStaticMesh* trafficLightStaticMesh = trafficLightMeshAsset.Object;

	trafficLightComponent->SetStaticMesh(trafficLightStaticMesh);
}

// Called when the game starts or when spawned
void AtrafficLightMesh::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AtrafficLightMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

