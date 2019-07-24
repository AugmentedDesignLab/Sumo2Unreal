#pragma once
#include "Engine.h"
#include "Platform.h"
#include <vector>


class walkingArea
{
	friend class UfileParser;
public:
	walkingArea();
	~walkingArea();

	void setWalkingAreaID(const TCHAR* tempID);
	void centroidCalculation();
	void trafficLightLocationCalculator();
	FVector directionVectorCalculator(float, float, float, float);
	void stopSignRotationCalculator();
	void getStopSignOrientation(FVector&);

private:
	bool NoTrafficLightatWalkingArea = false;
	FQuat trafficLight1Orientation;
	FVector trafficLight1Location;
	FQuat stopSignOrientation;
	float centroidX;
	float centroidY;
	FString walkingAreaID;
	std::vector<float> walkingAreaShapeCoordinates;
};