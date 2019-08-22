#pragma once
#include <utility>
#include <vector>
#include "RoadMesh.h"
#include "fileParser.h"


class simpleSidewalk {

	friend class UfileParser;

public:

	//constructor
	simpleSidewalk();
	~simpleSidewalk();

	//Setter Functions
	void SetID(const TCHAR*);
	void setLaneLength(const TCHAR*);
	void setFromID(const TCHAR*);
	void setToID(const TCHAR*);
	void setShapeCoordinates(const std::vector<float>&);

	//Getter Functions
	FString getID();
	FString getFromID();
	FString getToID();
	float getLaneLength();

	//Setting the vertices to be used during the edge mesh creation on UE4
	void setVertexCoordinates(float);

	//Spawn Function - Add some features to the mesh and spawn
	void SpawnEdgeMesh();


	/*
	double getMyLaneWidth();
	std::pair <double, double> getFirstShape();
	std::pair <double, double> getSecondShape();
	*/

	//just a tester since I don't have simpleNode yet
	//ignore these
	//simpleSidewalk::simpleSidewalk(FString id, FString fromNode, FString toNode, double length);


private:

	FString EdgeID;
	float LaneLength;
	FString fromID;
	FString toID;
	const float pi_value = std::acos(-1);

	TArray<FVector> vertexArray;
	TArray<FVector> newVertexArray; //Array to store new vertex locations(relative to the centroid) 
	TArray<float> vertexAnglesUnSorted;
	TArray<float> vertexAnglesSorted;

	FVector centroid;
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
	float laneWidth;

	//testers
	FString fromNodeID;
	FString toNodeID;
};
