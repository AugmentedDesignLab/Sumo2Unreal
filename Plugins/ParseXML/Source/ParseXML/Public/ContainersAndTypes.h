#pragma once
#include <vector>
#include <memory>
#include "Map.h"
#include "SimpleEdge.h"
#include "SimpleNode.h"
#include "trafficLight.h"
#include "StopSignMesh.h"
#include "walkingArea.h"
#include "SimpleSpline.h"

//List of sorted edges for a particular node
typedef std::vector<SimpleEdge*> EdgeVector;

//Shared pointer for every node object created
typedef std::unique_ptr<SimpleNode> SimpleNodePtr;
typedef std::unique_ptr<SimpleEdge> SimpleEdgePtr;
typedef std::unique_ptr<walkingArea> walkingAreaPtr;
typedef std::unique_ptr<trafficLight> trafficLightPtr;
#pragma warning(suppress : 4996)
typedef std::tr1::shared_ptr<SimpleSpline> SimpleSplinePtr;

//Node Map, Edge Map, walkingArea and trafficLight Map
typedef TMap<const TCHAR*, SimpleNodePtr> NodeTMap;
typedef TMap<FString, SimpleEdgePtr> EdgeTMap;
typedef TMap<const TCHAR*, walkingAreaPtr> walkingAreaTMap;
typedef TMap<const TCHAR*, trafficLight*> trafficLightTMap;
typedef TMap<const TCHAR*, AStopSignMesh*> StopSignTMap;
typedef TMap<FString, SimpleSplinePtr> SplineTMap;


class NodeCont
{
public:
	NodeCont() {};
	~NodeCont() {};

	//Maps to store the pointers to the parsed nodes (pointers to the objects created)
	NodeTMap NodeMap;
};

class EdgeCont
{
public:
	EdgeCont() {};
	~EdgeCont() {};

	//Map to store the pointers to the parsed edges (pointers to the objects created)
	EdgeTMap EdgeMap;
};

class walkingAreaCont
{
public:
	walkingAreaCont() {};
	~walkingAreaCont() {};


	//Map to store the pointers to the parsed walkingAreas (pointers to the objects created)
	walkingAreaTMap walkingAreaMap;
};

class trafficLightCont
{
public:
	trafficLightCont() {};
	~trafficLightCont() {};

	//Map to store the pointers to the parsed traffic lights (pointers to the objects created)
	trafficLightTMap trafficLightMap;
};

class splineCont {
public:
	splineCont() {};
	~splineCont() {};

	//Map to store pointers to spline objects.
	SplineTMap SplineMap;
};

class StopSignCont
{
public:
	StopSignCont() {};
	~StopSignCont() {};

	//Map to store the pointers to the parsed stop signs (pointers to the objects created)
	StopSignTMap StopSignMap;
};













