#include "walkingArea.h"

walkingArea::walkingArea()
{

}

walkingArea::~walkingArea()
{

}

void walkingArea::setWalkingAreaID(const TCHAR* tempID)
{
	walkingAreaID = FString(tempID);
	UE_LOG(LogEngine, Warning, TEXT("New walkingArea ID is %s"), tempID);
}

void walkingArea::centroidCalculation()
{
	float cumulativeX = 0;
	float cumulativeY = 0;
	for (int i = 0; i <= (walkingAreaShapeCoordinates.size() - 1); i++)
	{
		if ((i % 2) == 0)
		{
			cumulativeX = cumulativeX + walkingAreaShapeCoordinates[i];
		}
		else
		{
			cumulativeY = cumulativeY + walkingAreaShapeCoordinates[i];
		}
	}
	centroidX = cumulativeX / (walkingAreaShapeCoordinates.size() / 2);
	centroidY = cumulativeY / (walkingAreaShapeCoordinates.size() / 2);
}

FVector walkingArea::directionVectorCalculator(float x0, float y0, float x1, float y1)
{
	FVector position1;
	position1.X = x0;
	position1.Y = y0;
	position1.Z = 0.0f;

	FVector position2;
	position2.X = x1;
	position2.Y = y1;
	position2.Z = 0.0f;

	FVector directionVector = position2 - position1;

	return directionVector;
}

void walkingArea::trafficLightLocationCalculator()
{
	NoTrafficLightatWalkingArea = false;
	if (walkingAreaShapeCoordinates.size() > 12)
	{
		FVector directionVector = directionVectorCalculator(walkingAreaShapeCoordinates[0], walkingAreaShapeCoordinates[1], walkingAreaShapeCoordinates[2], walkingAreaShapeCoordinates[3]);
		//FVector rightVector = directionVector.ToOrientationQuat().GetRightVector();

		trafficLight1Location.X = walkingAreaShapeCoordinates[0];
		trafficLight1Location.Y = walkingAreaShapeCoordinates[1];
		trafficLight1Location.Z = -1.8f;

		trafficLight1Orientation = directionVector.ToOrientationQuat();
	}
	else
	{
		FVector directionVector = directionVectorCalculator(walkingAreaShapeCoordinates[2], walkingAreaShapeCoordinates[3], walkingAreaShapeCoordinates[4], walkingAreaShapeCoordinates[5]);
		//FVector rightVector = directionVector.ToOrientationQuat().GetRightVector();

		trafficLight1Location.X = walkingAreaShapeCoordinates[2];
		trafficLight1Location.Y = walkingAreaShapeCoordinates[3];
		trafficLight1Location.Z = -1.8f;

		trafficLight1Orientation = directionVector.ToOrientationQuat();
	}	
}

void walkingArea::stopSignRotationCalculator() {
	if (walkingAreaShapeCoordinates.size() > 12)
	{
		FVector directionVector = directionVectorCalculator(walkingAreaShapeCoordinates[0], walkingAreaShapeCoordinates[1], walkingAreaShapeCoordinates[2], walkingAreaShapeCoordinates[3]);
		getStopSignOrientation(directionVector);
	}
	else
	{
		FVector directionVector = directionVectorCalculator(walkingAreaShapeCoordinates[2], walkingAreaShapeCoordinates[3], walkingAreaShapeCoordinates[4], walkingAreaShapeCoordinates[5]);
		getStopSignOrientation(directionVector);
	}
}

void walkingArea::getStopSignOrientation(FVector& currentDirectionVector) {
	FRotator stopSignRotation = currentDirectionVector.ToOrientationQuat().GetRightVector().ToOrientationQuat().Rotator(); //Make the stop sign face the correct direction
	stopSignRotation.Roll += 90.0f; //Make the stop sign stand up
	stopSignOrientation = stopSignRotation.Quaternion(); //Convert to FQuat type to give it as an input while spawning the stopSign mesh.
}


