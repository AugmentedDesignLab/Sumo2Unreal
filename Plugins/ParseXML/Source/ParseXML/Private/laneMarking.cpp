#include "laneMarking.h"
#include "Engine.h"

// Sets default values
AlaneMarking::AlaneMarking()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> leftDecal(TEXT("Material'/Game/finalRoadMaterials/turnLaneArrow/left/Left_Arrow_MAT.Left_Arrow_MAT'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> rightDecal(TEXT("Material'/Game/finalRoadMaterials/turnLaneArrow/right/Right_MAT.Right_MAT'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> straightLeftDecal(TEXT("Material'/Game/finalRoadMaterials/turnLaneArrow/straightLeft/Lane_Markings_-_Left_Straight_MAT.Lane_Markings_-_Left_Straight_MAT'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> straightRightDecal(TEXT("Material'/Game/finalRoadMaterials/turnLaneArrow/straightRight/RightStraight_MAT.RightStraight_MAT'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> straightDecal(TEXT("Material'/Game/finalRoadMaterials/stopLine/Road_with_lane_markings_stop_MAT1.Road_with_lane_markings_stop_MAT1'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> pedestrianCrosswalkDecal(TEXT("Material'/Game/finalRoadMaterials/pedestrianFourLaneCrosswalk/Road_with_lane_markings_pedestrian_MAT.Road_with_lane_markings_pedestrian_MAT'"));
	if (leftDecal.Succeeded()) decalMaterialMap.Add("left", leftDecal.Object);
	if (rightDecal.Succeeded()) decalMaterialMap.Add("right", rightDecal.Object);
	if (straightLeftDecal.Succeeded()) decalMaterialMap.Add("straightLeft", straightLeftDecal.Object);
	if (straightRightDecal.Succeeded()) decalMaterialMap.Add("straightRight", straightRightDecal.Object);
	if (straightDecal.Succeeded()) decalMaterialMap.Add("straight", straightDecal.Object);
	if (pedestrianCrosswalkDecal.Succeeded()) decalMaterialMap.Add("pedestrianCrossswalk", pedestrianCrosswalkDecal.Object);
}

// Called when the game starts or when spawned
void AlaneMarking::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AlaneMarking::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AlaneMarking::spawnActor()
{
	FActorSpawnParameters SpawnParameters;
	FRotator decalRotation = directionVector.Rotation();
	decalRotation.Yaw += 90.0f;
	ADecalActor* decalActor = this->GetWorld()->SpawnActor<ADecalActor>(Spawnlocation, decalRotation, SpawnParameters);
}
