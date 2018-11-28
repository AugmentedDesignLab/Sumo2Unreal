#pragma once

//#include SimpleNode.h;
#include <utility>
#include <vector>
#include "EdgeMesh.h"
#include "fileParser.h"
#include "Engine.h"
#include "Platform.h"


class SimpleEdge {

	friend class UfileParser;

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

	//Setting the vertices to be used during the edge mesh creation on UE4
	void setVertexCoordinates();

	//Spawn Function - Add some features to the mesh and spawn
	void SpawnEdgeMesh();


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

	TArray<FVector> vertexArray; //Array to store vertices
	TArray<float> vertexAnglesUnSorted;
	TArray<float> vertexAnglesSorted;
	
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
	int32 laneWidth = 4;

	//testers
	FString fromNodeID;
	FString toNodeID;
};