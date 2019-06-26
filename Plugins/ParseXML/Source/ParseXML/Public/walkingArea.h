#ifndef WALKINGAREA_HEADER
#define WALKINGAREA_HEADER
#include "ContainersAndTypes.h"
#include "Platform.h"
#include "Engine.h"
#include <vector>

//class declaration
class UfileParser;

class walkingArea
{
	friend class UfileParser;
public:
	walkingArea();
	~walkingArea();

	void setWalkingAreaID(const TCHAR* tempID);
	void centroidCalculation();


private:
	float centroidX;
	float centroidY;
	FString walkingAreaID;
	std::vector<float> walkingAreaShapeCoordinates;
};

#endif