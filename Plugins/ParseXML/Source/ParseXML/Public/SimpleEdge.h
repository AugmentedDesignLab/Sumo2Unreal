#pragma once

//#include SimpleNode.h;
#include <utility>
#include <vector>
#include "Engine.h"


class SimpleEdge {



public:

	//constructor
	SimpleEdge();


	void setId(FString id);
	void setLaneLength(double length);
	void setLaneWidth(double width);
	void setFrom(FString fromNode);
	void setTo(FString toNode);
	void setFirstShape(std::pair<double, double> shape);
	void setSecondShape(std::pair<double, double> shape);

	
	FString getID();
	FString getFromID();
	FString getToID();
	double getMyLaneLength();
	double getMyLaneWidth();
	std::pair <double, double> getFirstShape();
	std::pair <double, double> getSecondShape();

	//just a tester since I don't have simpleNode yet
	//ignore these
	SimpleEdge::SimpleEdge(FString id, FString fromNode, FString toNode, double length);


private:

	FString myID;

	float myLaneLength;
	double myLaneWidth;

	double shapeX1;
	double shapeY1;

	std::pair <double, double> firstShape;
	std::pair <double, double> secondShape;

	std::vector<float> edgeShapeCoordinates;

	double shapeX2;
	double shapeY2;


	//testers
	FString myFromID;
	FString myToID;

};