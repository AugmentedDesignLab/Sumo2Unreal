// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleAIController.h"
#include <Runtime\AIModule\Classes\BehaviorTree\BehaviorTree.h>
#include "WayPoint.h"
#include "WheeledVehicleObject.h"
#include "Kismet/KismetMathLibrary.h"


//runs at the second Tick
AVehicleAIController::AVehicleAIController()
{
	PrimaryActorTick.bCanEverTick = true;
	//PrintLog("Inside controller constructor");
	
	//Creating subobject 
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("VehicleBehaviorTree");
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>("VehicleBlackBoard");
}

//Runs at the third Tick
void AVehicleAIController::BeginPlay()
{
	Super::BeginPlay();

	PrintLog("Inside controller beginplay");

}

void AVehicleAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//PrintLog("Inside controller tick ");
	//updating steering value each frame. 
	BlackboardComponent->SetValueAsFloat("SteerValue", UpdatedSteeringValue(DeltaTime));
	// Update distance value in the blackboard
	float DistanceAlongWayPoint = BlackboardComponent->GetValueAsFloat("DistanceAlongWayPoint");
}


/*
 *Update the steering value. Get the vehicle object, waypoint, Distance covered,  from Blackboard
 * 
 */
float AVehicleAIController::UpdatedSteeringValue(float Delta)
{
	AWayPoint* WayPoint = Cast<AWayPoint>(BlackboardComponent->GetValueAsObject("WayPoint"));
	AWheeledVehicleObject* Vehicle = Cast<AWheeledVehicleObject>(BlackboardComponent->GetValueAsObject("VehicleObject"));
	float DistanceAlongWayPoint = BlackboardComponent->GetValueAsFloat("DistanceAlongWayPoint");
	
	float steer_value = 0.0;
	VehicleVelocity = Vehicle->GetVelocity();
	FVector delta_distance = VehicleVelocity * Delta * 0.036;
	float distance_value = delta_distance.Size() * 27.78;

	DistanceAlongWayPoint += distance_value;
	//PrintLog("Distance along spline" + FString::SanitizeFloat(DistanceAlongWayPoint));
	BlackboardComponent->SetValueAsFloat("DistanceAlongWayPoint", DistanceAlongWayPoint);

	FVector veh_loc = Vehicle->GetActorLocation();

	FVector veh_forward = Vehicle->GetActorForwardVector();  //Vehicle->GetVehicleForward();
	UKismetSystemLibrary::DrawDebugArrow(this, veh_loc, veh_loc + veh_forward * 1000, 500, FColor::Red, 0.1, 20);

	FVector next_direction = WayPoint->SplineComponent->GetDirectionAtDistanceAlongSpline(DistanceAlongWayPoint, ESplineCoordinateSpace::World);
	UKismetSystemLibrary::DrawDebugArrow(this, veh_loc, veh_loc + next_direction * 1000, 500, FColor::Blue, 0.1, 20);

	FVector nearest_spline_point = WayPoint->SplineComponent->FindLocationClosestToWorldLocation(veh_loc, ESplineCoordinateSpace::World);

	FVector veh_move_direction = (nearest_spline_point - veh_loc);
	veh_move_direction.Z = 0;
	float distance_threshold = BlackboardComponent->GetValueAsFloat("ThreshWaypointDeviation");

	if (veh_move_direction.Size() > distance_threshold) {
		veh_move_direction = veh_move_direction.GetSafeNormal();
	}
	else {
		veh_move_direction = FVector::ZeroVector;
	}

	UKismetSystemLibrary::DrawDebugArrow(this, veh_loc, veh_loc + veh_move_direction * 1000, 500, FColor::Magenta, 0.1, 20);

	//resultant from 3 vector
	FVector resultant_vector = (next_direction + veh_forward + veh_move_direction);
	resultant_vector = resultant_vector.GetSafeNormal();
	UKismetSystemLibrary::DrawDebugArrow(this, veh_loc, veh_loc + resultant_vector * 1000, 500, FColor::Cyan, 0.1, 20);

	float dot_product = FMath::RadiansToDegrees(acosf(FVector::DotProduct(veh_forward, resultant_vector)));
	FVector cross_product = FVector::CrossProduct(veh_forward, resultant_vector);

	if (cross_product.Z >= 0)
	{
		steer_value = UKismetMathLibrary::MapRangeClamped(dot_product, 0, 90, 0, 1);
	}
	else {
		steer_value = UKismetMathLibrary::MapRangeClamped(dot_product, 0, 90, 0, -1);
	}


	return steer_value;
}

bool AVehicleAIController::InitializeBehaviorTree(FString BTPath)
{
	BehaviorTreeAsset = LoadObjFromPath<UBehaviorTree>(FName(*BTPath));
	if (BehaviorTreeAsset != NULL)
	{
		float randomspeed = UKismetMathLibrary::RandomFloatInRange(0.50, 0.55);
		float randomdevthres = UKismetMathLibrary::RandomFloatInRange(5.0, 12.0);
		BlackboardComponent->InitializeBlackboard(*BehaviorTreeAsset->BlackboardAsset);
		BlackboardComponent->SetValueAsFloat("BrakeValue", 0.0);
		BlackboardComponent->SetValueAsFloat("SteerValue", 0.0);
		BlackboardComponent->SetValueAsFloat("ThrottleValue", randomspeed);
		BlackboardComponent->SetValueAsFloat("ThreshWaypointDeviation", randomdevthres);
		BlackboardComponent->SetValueAsFloat("ThreshStopAtStopSignDistance", 800);
		PrintLog("Behavior tree and blackboard init");
		return true;
	}
	else
	{
		PrintLog("Behavior Asset not found");
		return false;
	}
}

bool AVehicleAIController::RunBehaviorTree()
{
	BehaviorTreeComponent->StartTree(*BehaviorTreeAsset);
	// need to check why this still works :')
	return false;
}

FVector AVehicleAIController::GetVehicleVelocity()
{
	return VehicleVelocity;
}
