// Fill out your copyright notice in the Description page of Project Settings.

#include "VehicleController.h"
#include "VehicleMovement.h"
#include "EngineUtils.h"
#include <Runtime\AIModule\Classes\BehaviorTree\BehaviorTree.h>
#include "Engine.h"
#include "UnrealMathUtility.h"
#include "Kismet/KismetMathLibrary.h"


AVehicleController::AVehicleController() 
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>("VehicleBlackBoard");
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>("VehicleBehaviorTree");
	//perception setup
	AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerception");
	AIPerceptionSigntComp = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	if (AIPerceptionComp && AIPerceptionSigntComp)
	{
		AIPerceptionComp->ConfigureSense(*AIPerceptionSigntComp);
		AIPerceptionComp->SetDominantSense(AIPerceptionSigntComp->GetSenseImplementation());

		AIPerceptionSigntComp->SightRadius = 3000.0f;
		AIPerceptionSigntComp->LoseSightRadius = 3100.0f;
		AIPerceptionSigntComp->PeripheralVisionAngleDegrees = 45.0f;

		AIPerceptionSigntComp->DetectionByAffiliation.bDetectEnemies = true;
		AIPerceptionSigntComp->DetectionByAffiliation.bDetectFriendlies = true;
		AIPerceptionSigntComp->DetectionByAffiliation.bDetectNeutrals = true;
	}

	AIPerceptionComp->OnPerceptionUpdated.AddDynamic(this, &AVehicleController::ProcessPerceivedInformation);
	//GetPercComp()->OnPerceptionUpdated.AddDynamic(this, &AMyAIController::ProcessPerceivedInformation);
	PrimaryActorTick.bCanEverTick = true;
}


void AVehicleController::ProcessPerceivedInformation(const TArray<AActor*>& UpdatedActors)
{
	for (int i = 0; i < UpdatedActors.Num(); i++)
	{
		AActor* temp = UpdatedActors[i];
		PrintLog("Name " + temp->GetName());
		
		if (temp->GetName().Contains("StopSign"))
		{
			StopSignLocation.AddUnique(temp->GetActorLocation());
			StopSignLocation.Sort(FVectorSortByDistance(Vehicle->GetVehicleLocation()));
			BlackboardComp->SetValueAsVector("StopSign", StopSignLocation[0]);
			PrintLog("Setting stop sign ahead true");
			BlackboardComp->SetValueAsBool("IsStopSignAhead", true);
		
		}
		else if (temp->GetName().Contains("Car"))
		{
			AVehicleMovement* temp_vehicle_controller = (AVehicleMovement*)temp;
			if (temp_vehicle_controller != nullptr)
			{
				//PrintLog(FString::FromInt(temp_vehicle_controller->GetWayPoint()->ID));
				OtherVehicle.AddUnique(temp_vehicle_controller);
				for (int i = 0; i < OtherVehicle.Num(); i++)
				{
					if (OtherVehicle[i]->GetWayPoint()->ID == this->Vehicle->GetWayPoint()->ID)
					{
						OtherVehicleOnSpline = OtherVehicle[i];
						BlackboardComp->SetValueAsBool("IsVehicleAhead", true);
					}
				}
				
				
			}
		}
		else
		{
			PrintLog("False");
		}
		
	}
}


void AVehicleController::BeginPlay()
{
	Super::BeginPlay();
	Vehicle = Cast<AVehicleMovement>(this->GetPawn());
	SpeedLimit = Vehicle->GetLastControl().SpeedLimit;

	if (Vehicle && Vehicle->VehicleBehavior)
	{
		BlackboardComp->InitializeBlackboard(*(Vehicle->VehicleBehavior->BlackboardAsset));
		BehaviorComp->StartTree(*(Vehicle->VehicleBehavior));
	}
	this->SetPerceptionComponent(*AIPerceptionComp);

	BlackboardComp->SetValueAsBool("IsNormalRoad", true);
	BlackboardComp->SetValueAsBool("IsStopSignAhead", false);
	BlackboardComp->SetValueAsBool("IsVehicleAhead", false);
	
	//PrintLog("inside controller beginplay" + FString::SanitizeFloat(Vehicle->LastControl.SteeringValue));
}

void AVehicleController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpeedLimit = Vehicle->GetLastControl().SpeedLimit;
	IsNormalRoad = BlackboardComp->GetValueAsBool("IsNormalRoad");

	float steer_value = CalculateSteeringValue(DeltaTime);
	float throttle_value;


	if (IsNormalRoad) 
	{
		throttle_value = Move(Vehicle->GetVehicleVelocity().Size() * 0.036);
		Vehicle->SetSteeringValue(steer_value);
		Vehicle->SetThrottleValue(throttle_value);
	}
	else
	{
		//throttle_value = Stop(Vehicle->GetVehicleVelocity().Size() * 0.036);
		Vehicle->SetBrakeValue(0.3);
		Vehicle->SetSteeringValue(steer_value);
		Vehicle->SetThrottleValue(0);
	}
	Vehicle->SetControl();
}

AVehicleMovement* AVehicleController::GetVehicleFromController()
{
	return Vehicle;
}



float AVehicleController::CalculateSteeringValue(float delta)
{
	float steer_value = 0.0;
	FVector delta_distance = Vehicle->GetVelocity() * delta * 0.036;
	float distance_value = delta_distance.Size() * 27.78;
	Vehicle->SetTraveledDistance(Vehicle->GetTraveledDistance() + distance_value);
	FVector veh_loc = Vehicle->GetActorLocation();

	FVector veh_forward = Vehicle->GetVehicleForward();
	UKismetSystemLibrary::DrawDebugArrow(this, veh_loc, veh_loc + veh_forward * 1000, 500, FColor::Red, 0.1, 20);

	FVector next_direction = Vehicle->LastControl.WayPoint->SplineComponent->GetDirectionAtDistanceAlongSpline(Vehicle->GetTraveledDistance(), ESplineCoordinateSpace::World);
	UKismetSystemLibrary::DrawDebugArrow(this, veh_loc, veh_loc + next_direction * 1000, 500, FColor::Blue, 0.1, 20);

	FVector nearest_spline_point = Vehicle->LastControl.WayPoint->SplineComponent->FindLocationClosestToWorldLocation(veh_loc, ESplineCoordinateSpace::World);
	
	FVector veh_move_direction = (nearest_spline_point - veh_loc);
	veh_move_direction.Z = 0;
	if (veh_move_direction.Size() > Vehicle->LastControl.DistanceThreshold) {
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

void AVehicleController::VahicleBrake(float BrakeValue)
{
	Vehicle->SetBrakeValue(BrakeValue);
}




float AVehicleController::Move(float Speed)
{
	//PrintLog("Speed " + FString::SanitizeFloat(Speed));
	if (Speed >= SpeedLimit)
	{
		return Stop(Speed);
	}
	else if (Speed >= SpeedLimit - 10.0f)
	{
		return 0.5f;
	}
	else
	{
		return 1.0f;
	}
}

float AVehicleController::Stop(float Speed)
{
	return (Speed >= 1.0f ? -Speed / SpeedLimit : 0.0f);
}

void AVehicleController::PrintLog(FString Text)
{
	if (!GEngine) return;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, *Text);
}
