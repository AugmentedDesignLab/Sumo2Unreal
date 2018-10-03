#pragma once

//#include SimpleNode.h;
#include <utility>
#include <vector>
#include "Engine.h"
#include "Platform.h"


class SimpleEdge {

public:

	//constructor
	SimpleEdge();
	~SimpleEdge();

	//Setter Functions
	void SetID(const TCHAR*);
	void setLaneLength(const TCHAR*);
	void setFromID(const TCHAR*);
	void setToID(const TCHAR*);
	void setShapeCoordinates(const std::vector<float>&);

	/*
	void setLaneLength(double length);
	void setLaneWidth(double width);
	void setFrom(FString fromNode);
	void setTo(FString toNode);
	void setFirstShape(std::pair<double, double> shape);
	void setSecondShape(std::pair<double, double> shape);
	*/

	//Getter Functions
	FString getID();
	FString getFromID();
	FString getToID();
	float getLaneLength();

	/*
	double getMyLaneWidth();
	std::pair <double, double> getFirstShape();
	std::pair <double, double> getSecondShape();
	*/

	//just a tester since I don't have simpleNode yet
	//ignore these
	//SimpleEdge::SimpleEdge(FString id, FString fromNode, FString toNode, double length);


private:

	FString EdgeID;
	float LaneLength;
	FString fromID;
	FString toID;
	
	/*
	double myLaneWidth;
	double shapeX1;
	double shapeY1;
	std::pair <double, double> firstShape;
	std::pair <double, double> secondShape;
	double shapeX2;
	double shapeY2;
	*/

	std::vector<float> edgeShapeCoordinates;

	//testers
	FString fromNodeID;
	FString toNodeID;
};