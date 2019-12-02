// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleSpawner.h"
#include "Engine.h"


// Sets default values
AVehicleSpawner::AVehicleSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrintLog("Inside constructor spawner");

}

// Called when the game starts or when spawned
void AVehicleSpawner::BeginPlay()
{
	Super::BeginPlay();
	PrintLog("Inside beginplay() spawner");
	TArray<AActor*> SplineActors;
	TArray<AWayPoint*> Waypoints;
	SplineActors = FindAllWaypoint();
	
	for (int i = 0; i < SplineActors.Num(); i++)
	{
		Waypoints.Add((AWayPoint*)SplineActors[i]);
	}

	AWheeledVehicleObject* temp = Spawn((SplineActors)[22]->GetActorLocation());

	temp->InitializeWheeledVehicle(Waypoints[22]);

	
}

// Called every frame
void AVehicleSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AWheeledVehicleObject* AVehicleSpawner::Spawn(FVector Location)
{
	if (ToSpawn)
	{
		UWorld* world = GetWorld();
		Location = FVector(Location.X, Location.Y, 20);
		if (world)
		{
			FActorSpawnParameters spawn_param;
			spawn_param.Owner = this;
			FRotator rotator;
			PrintLog(Location.ToString());
			AWheeledVehicleObject* temp = world->SpawnActor<AWheeledVehicleObject>(ToSpawn, Location, rotator, spawn_param);
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

TArray<AActor*> AVehicleSpawner::FindAllWaypoint()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWayPoint::StaticClass(), FoundActors);
	return FoundActors;
}

void AVehicleSpawner::PrintLog(FString Text)
{
	if (!GEngine) return;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, *Text);
}

