// Fill out your copyright notice in the Description page of Project Settings.

#include "CarSpawner.h"

#include "Engine.h"


// Sets default values
ACarSpawner::ACarSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

AVehicleMovement* ACarSpawner::Spawn(FVector Location)
{
	if (ToSpawn)
	{
		UWorld* world = GetWorld();
		Location = FVector(Location.X, Location.Y, SpawnHeight);
		if (world)
		{
			FActorSpawnParameters spawn_param;
			spawn_param.Owner = this;
			FRotator rotator;
			PrintLog(Location.ToString());
			AVehicleMovement* temp = world->SpawnActor<AVehicleMovement>(ToSpawn, Location, rotator, spawn_param);
			return temp;
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		return NULL;
	}
}

TArray<AActor*> ACarSpawner::FindAllWaypoint()
{
	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWayPoint::StaticClass(), FoundActors);
	
	return FoundActors;
}



// Called when the game starts or when spawned
void ACarSpawner::BeginPlay()
{
	Super::BeginPlay();
	//PrintLog("Calling find all waypoint");
	TArray<AActor*> SplineActors;
	SplineActors = FindAllWaypoint();
	for (int i = 0; i < SplineActors.Num(); i++)
	{
		//PrintLog("Spawning car " + (SplineActors)[i]->GetActorLocation().ToString());
		//Spawn((SplineActors)[i]->GetActorLocation());
	}
	AVehicleMovement* temp = Spawn((SplineActors)[26]->GetActorLocation());
	AWayPoint* way_point = (AWayPoint*)(SplineActors)[26];
	temp->Initialize(way_point, 20);

}

// Called every frame
void ACarSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

	
}

void ACarSpawner::PrintLog(FString Text)
{
	if (!GEngine) return;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, *Text);
}
