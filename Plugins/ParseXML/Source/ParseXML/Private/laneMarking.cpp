#include "laneMarking.h"
#include "Engine.h"

// Sets default values
AlaneMarking::AlaneMarking()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UMaterial> leftDecal(TEXT("Material'/Game/finalRoadMaterials/turnLaneArrow/left/Lane_Markings_MAT.Lane_Markings_MAT'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> rightDecal(TEXT("Material'/Game/finalRoadMaterials/turnLaneArrow/right/Lane_Markings_MAT_R.Lane_Markings_MAT_R'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> straightLeftDecal(TEXT("Material'/Game/finalRoadMaterials/turnLaneArrow/straightLeft/Lane_Markings_MAT_SL.Lane_Markings_MAT_SL'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> straightRightDecal(TEXT("Material'/Game/finalRoadMaterials/turnLaneArrow/straightRight/Lane_Markings_MAT_SR.Lane_Markings_MAT_SR'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> straightDecal(TEXT("Material'/Game/finalRoadMaterials/stopLine/Road_with_lane_markings_stop_MAT.Road_with_lane_markings_stop_MAT'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> pedestrianCrosswalkDecal(TEXT("Material'/Game/finalRoadMaterials/pedestrianFourLaneCrosswalk/Road_with_lane_markings_pedestrian_MAT.Road_with_lane_markings_pedestrian_MAT'"));
	if (leftDecal.Succeeded()) decalMaterialMap.Add("left", leftDecal.Object);
	if (rightDecal.Succeeded()) decalMaterialMap.Add("right", rightDecal.Object);
	if (straightLeftDecal.Succeeded()) decalMaterialMap.Add("straightLeft", straightLeftDecal.Object);
	if (straightRightDecal.Succeeded()) decalMaterialMap.Add("straightRight", straightRightDecal.Object);
	if (straightDecal.Succeeded()) decalMaterialMap.Add("straight", straightDecal.Object);
	if (pedestrianCrosswalkDecal.Succeeded()) decalMaterialMap.Add("pedestrianCrosswalk", pedestrianCrosswalkDecal.Object);
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
	UE_LOG(LogEngine, Warning, TEXT("Spawning!!"));
	FActorSpawnParameters SpawnParameters;
	FRotator decalRotation = directionVector.Rotation();
	decalRotation.Yaw += 90.0f;
	ADecalActor* decalActor = this->GetWorld()->SpawnActor<ADecalActor>(Spawnlocation, decalRotation, SpawnParameters);
	decalComponent = decalActor->GetDecal();
	decalComponent->DecalSize = FVector(128.0f, 278.0908813f, 188.199707f);
	if (currentDecalSelection.Equals(TEXT("left"))) decalComponent->SetDecalMaterial(decalMaterialMap["left"]);
	else if (currentDecalSelection.Equals(TEXT("right"))) decalComponent->SetDecalMaterial(decalMaterialMap["right"]);
	else if (currentDecalSelection.Equals(TEXT("straightLeft"))) decalComponent->SetDecalMaterial(decalMaterialMap["straightLeft"]);
	else if (currentDecalSelection.Equals(TEXT("straightRight"))) decalComponent->SetDecalMaterial(decalMaterialMap["straightRight"]);
	else if (currentDecalSelection.Equals(TEXT("straight"))) decalComponent->SetDecalMaterial(decalMaterialMap["straight"]);
}

void AlaneMarking::spawnPedestrianCrossingDecal()
{
	FActorSpawnParameters SpawnParameters;
	FRotator decalRotation = directionVector.Rotation();
	ADecalActor* decalActor = this->GetWorld()->SpawnActor<ADecalActor>(Spawnlocation, decalRotation, SpawnParameters);
	decalComponent = decalActor->GetDecal();
	decalComponent->DecalSize = FVector(128.0f, 172.5901642f, 487.2773743f);
	decalComponent->SetDecalMaterial(decalMaterialMap["pedestrianCrosswalk"]);
}
