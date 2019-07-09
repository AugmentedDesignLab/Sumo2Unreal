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

/*
FVector walkingArea::trafficLightLocation()
{
	
}
*/
