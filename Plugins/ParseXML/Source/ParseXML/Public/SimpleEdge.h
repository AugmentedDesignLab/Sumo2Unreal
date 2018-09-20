#pragma once
#pragma once

//#include SimpleNode.h;
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

	
	FString getID();
	FString getFromID();
	FString getToID();
	FString getMyShape();
	double getMyLaneLength();
	double getMyLaneWidth();

	//just a tester since I don't have simpleNode yet
	//ignore these
	SimpleEdge::SimpleEdge(FString id, FString fromNode, FString toNode, double length);


public:

	FString myID;

	double myLaneLength;
	double myLaneWidth;

	FString myShape;


	//testers
	FString myFromID;
	FString myToID;

};