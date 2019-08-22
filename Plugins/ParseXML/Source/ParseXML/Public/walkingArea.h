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
	FVector trafficControlLocationCalculator();
	FVector directionVectorCalculator(float, float, float, float);
	FQuat stopSignRotationCalculator();
	FQuat getStopSignOrientation(FVector&);

private:
	bool NoTrafficLightatWalkingArea = false;
	FQuat trafficLight1Orientation;
	FVector trafficControlLocation;
	FQuat stopSignOrientation;
	float centroidX;
	float centroidY;
	FString walkingAreaID;
	std::vector<float> walkingAreaShapeCoordinates;
};