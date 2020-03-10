// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleSpawner.h"



// Sets default values
AVehicleSpawner::AVehicleSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//PrintLog("Inside constructor spawner");

}

// Called when the game starts or when spawned
void AVehicleSpawner::BeginPlay()
{
	Super::BeginPlay();
	temp = 0;
	spawning = 0;
	//PrintLog("Inside beginplay() spawner");
	SplineActors = FindAllWaypoint();
	
	for (int i = 0; i < SplineActors.Num(); i++)
	{
		Waypoints.Add((AWayPoint*)SplineActors[i]);
	}
	VehicleList.Sort(AVehicleSpawner::Comparison);
	//PrintLog("First vehicle " + FString::SanitizeFloat(VehicleList[0].SpawnAfterSec));
	//PrintLog("last vehicle " + FString::SanitizeFloat(VehicleList[VehicleList.Num() - 1].SpawnAfterSec));
}

// Called every frame
void AVehicleSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	temp += DeltaTime;

	//PrintLog(" spawning  " + FString::SanitizeFloat(spawning) + " VehicleList.Num() " + FString::SanitizeFloat(VehicleList.Num()));
	if(spawning < VehicleList.Num())
	{
		if(temp > VehicleList[spawning].SpawnAfterSec)
		{
			FVehicleSpecification Vehicle = VehicleList[spawning];
			//PrintLog("Spawning car " + FString::SanitizeFloat(Vehicle.SpawnAfterSec));
			APawn* t = SpawnVehicle(Vehicle.VehicleObject, Vehicle.Spline, Vehicle.SpawnDistanceOnSpline, 20.0);
			Vehicle.Spline->VehiclePawnList.Add(t);
			spawning++;
		}

	}
	else
	{
		//PrintLog("else ");
	}

}

APawn* AVehicleSpawner::SpawnVehicle(TSubclassOf<class AWheeledVehicleObject> VehicleObject, AWayPoint* WayPoint, float DistanceAlongSpline, float SpawnHeight = 20.0F)
{
	if (!VehicleObject) return nullptr;
	UWorld* world = GetWorld();
	if (!world) return nullptr;
	FVector LocationVector = WayPoint->SplineComponent->GetLocationAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::World);
	FVector SpawnLocation = FVector(LocationVector.X, LocationVector.Y, SpawnHeight);
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
	//PrintLog("end " + end.ToString() + " Angle " + FString::SanitizeFloat(angle) + " del " + FString::SanitizeFloat(del));
	FRotator rotator = FRotator(0, angle, 0);
	APawn* temp = world->SpawnActor<APawn>(VehicleObject, SpawnLocation, rotator, spawn_param);
	//PrintLog("spawning actor " + temp->GetName());
	AWheeledVehicleObject* t = Cast<AWheeledVehicleObject>(temp);
	t->InitializeWheeledVehicle(WayPoint);
	return temp;

}



TArray<AActor*> AVehicleSpawner::FindAllWaypoint()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWayPoint::StaticClass(), FoundActors);
	return FoundActors;
}