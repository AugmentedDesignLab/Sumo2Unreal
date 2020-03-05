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
	SplineActors = FindAllWaypoint();
	
	for (int i = 0; i < SplineActors.Num(); i++)
	{
		PrintLog("Spline name " + SplineActors[i]->GetFName().ToString());
		Waypoints.Add((AWayPoint*)SplineActors[i]);
	}

	FVector LocationVector = Waypoints[SpawningSplineID[spawning]]->SplineComponent->GetLocationAtDistanceAlongSpline(6000, ESplineCoordinateSpace::World);
	AWheeledVehicleObject* temp = Spawn(LocationVector, Waypoints[SpawningSplineID[spawning]]);
	spawning += 1;

	/*
	for (int i = 0; i < SpawningSplineID.Num(); i++) {

		FVector LocationVector = Waypoints[SpawningSplineID[i]]->SplineComponent->GetLocationAtDistanceAlongSpline(150, ESplineCoordinateSpace::World);
		AWheeledVehicleObject* temp = Spawn( LocationVector, Waypoints[SpawningSplineID[i]]);
	}
	*/
	
	

}

// Called every frame
void AVehicleSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	temp += DeltaTime;
	if (temp > SpawnTickTime && spawning < SpawningSplineID.Num()) {
		temp = 0;
		FVector LocationVector = Waypoints[SpawningSplineID[spawning]]->SplineComponent->GetLocationAtDistanceAlongSpline(150, ESplineCoordinateSpace::World);
		AWheeledVehicleObject* temp = Spawn(LocationVector, Waypoints[SpawningSplineID[spawning]]);
		spawning += 1;
		if (spawning == SpawningSplineID.Num()) {
			spawning = 0;
		}
	}
}

AWheeledVehicleObject* AVehicleSpawner::Spawn(FVector Location, AWayPoint* WayPoint)
{
	if (ToSpawn)
	{
		UWorld* world = GetWorld();
		Location = FVector(Location.X, Location.Y, 20);
		if (world)
		{
			FActorSpawnParameters spawn_param;
			spawn_param.Owner = this;
			FVector start = FVector(1, 0, 0);
			FVector end = WayPoint->SplineComponent->GetDirectionAtDistanceAlongSpline(WayPoint->SplineComponent->GetSplineLength() * 0.5f, ESplineCoordinateSpace::World);
			float angle = acos(FVector::DotProduct(start, end)) * 180 / 3.14159;
			float del = start.X * end.Y - end.X * start.Y;
			if (del < 0)
			{
				angle = 360 - angle;
			}
			PrintLog("end " + end.ToString() + " Angle " + FString::SanitizeFloat(angle) + " del " + FString::SanitizeFloat(del));
			FRotator rotator = FRotator(0, angle, 0);
			AWheeledVehicleObject* temp = world->SpawnActor<AWheeledVehicleObject>(ToSpawn, Location, rotator, spawn_param);
			temp->InitializeWheeledVehicle(WayPoint);
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
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, *Text);
}

