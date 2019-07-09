#pragma once
#include "Engine.h"
#include "Platform.h"

class trafficLight
{
	friend class UfileParser;
public:
	trafficLight();
	~trafficLight();

private:
	FString trafficLightID;
	FVector trafficLightLocation;
};