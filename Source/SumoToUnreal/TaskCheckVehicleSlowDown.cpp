// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskCheckVehicleSlowDown.h"
#include "VehicleAIController.h"

EBTNodeResult::Type UTaskCheckVehicleSlowDown::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBehaviorTreeComponent& MyComp = OwnerComp;
	AVehicleAIController* MyController = &MyComp ? Cast<AVehicleAIController>(MyComp.GetOwner()) : NULL;
	if (MyController == NULL)
	{
		return EBTNodeResult::Failed;
	}
	TArray<AActor*> VehicleActor = FindAllVehicleActor();
	for (AActor* Vehicle : VehicleActor)
	{
		AVehicleAIController* controller = Cast<AVehicleAIController>(Vehicle);
		//PrintLog("other pawn name " + controller->GetName() + " My name " + MyController->GetName());
		if(controller != MyController)
		{
			FVector MyLocation = MyController->GetPawn()->GetActorLocation();
			FVector OtherVehicleLocation = Vehicle->GetActorLocation();
			float distance = FVector::Distance(MyLocation, OtherVehicleLocation);
			PrintLog("Distance " + FString::SanitizeFloat(distance));
			if(distance < ThresholdVehicleDistance)
			{
				PrintLog("Crit distance ");
				float BrakeValue = MyController->BlackboardComponent->GetValueAsFloat("BrakeValue");
				float ThrottleValue = MyController->BlackboardComponent->GetValueAsFloat("ThrottleValue");
				if(BrakeValue <= 1) BrakeValue = BrakeValue + 0.1;
				if(ThrottleValue >= 0) ThrottleValue = ThrottleValue - 0.001;
				MyController->BlackboardComponent->SetValueAsFloat("BrakeValue", BrakeValue);
				MyController->BlackboardComponent->SetValueAsFloat("ThrottleValue", ThrottleValue);
				return EBTNodeResult::Succeeded;
			}
			else
			{
				//PrintLog("Increasing speed a little");
				float BrakeValue = MyController->BlackboardComponent->GetValueAsFloat("BrakeValue");
				float ThrottleValue = MyController->BlackboardComponent->GetValueAsFloat("ThrottleValue");
				if (BrakeValue >= 0) BrakeValue = BrakeValue - 0.1;
				if (ThrottleValue <= 1) ThrottleValue = ThrottleValue + 0.00001;
				MyController->BlackboardComponent->SetValueAsFloat("BrakeValue", BrakeValue);
				MyController->BlackboardComponent->SetValueAsFloat("ThrottleValue", ThrottleValue);
			}
		}
	}
	return  EBTNodeResult::Failed;
}

TArray<AActor*> UTaskCheckVehicleSlowDown::FindAllVehicleActor()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AVehicleAIController::StaticClass(), FoundActors);
	return FoundActors;
}
