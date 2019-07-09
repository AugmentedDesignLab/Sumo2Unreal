#pragma once
#include <vector>
#include <memory>
#include "Map.h"
#include "SimpleEdge.h"
#include "SimpleNode.h"
#include "trafficLight.h"
#include "walkingArea.h"

//List of sorted edges for a particular node
typedef std::vector<SimpleEdge*> EdgeVector;

//Node Map, Edge Map, walkingArea and trafficLight Map
typedef TMap<const TCHAR*, std::unique_ptr<SimpleNode>> NodeTMap;
typedef TMap<const TCHAR*, std::unique_ptr<SimpleEdge>> EdgeTMap;
typedef TMap<const TCHAR*, std::unique_ptr<walkingArea>> walkingAreaTMap;
typedef TMap<const TCHAR*, trafficLight*> trafficLightTMap;

//Shared pointer for every node object created
typedef std::unique_ptr<SimpleNode> SimpleNodePtr;
typedef std::unique_ptr<SimpleEdge> SimpleEdgePtr;
typedef std::unique_ptr<walkingArea> walkingAreaPtr;
typedef std::unique_ptr<trafficLight> trafficLightPtr;


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

	//Map to store the pointers to the parsed walkingAreas (pointers to the objects created)
	trafficLightTMap trafficLightMap;
};













