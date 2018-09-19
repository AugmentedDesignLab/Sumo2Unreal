#pragma once
#pragma once

//#include SimpleNode.h;
#include "Engine.h"

class SimpleEdge {



public:

	//SimpleEdge(FString id, SimpleNode* fromNode, SimpleNode* toNode, double length, FString shape);


	void setId(FString id);
	//void setFrom(SimpleNode* fromNode);
	//void setTo(SimpleNode* toNode);
	void setLaneLength(double length);
	void setLaneWidth(double width);

	//just a tester since I don't have simpleNode yet
	SimpleEdge::SimpleEdge(FString id, FString fromNode, FString toNode, double length);
	void setFrom(FString fromNode);
	void setTo(FString toNode);

private:

	FString myID;

	//SimpleNode* myFrom;
	//SimpleNode* myTo;

	double myLaneLength;
	double myLaneWidth;

	FString myShape;


	//testers
	FString myToTest;
	FString myFromTest;

};