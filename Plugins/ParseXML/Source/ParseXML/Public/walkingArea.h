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
	//FVector trafficLightLocation();


private:
	float centroidX;
	float centroidY;
	FString walkingAreaID;
	std::vector<float> walkingAreaShapeCoordinates;
};