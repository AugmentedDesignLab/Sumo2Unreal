#pragma once
#include "Runtime/XmlParser/Public/FastXml.h"
#include "Runtime/XmlParser/Public/XmlParser.h"
#include "Runtime/Core/Public/Containers/Map.h"
#include "trafficLightMesh.h"
#include "StopSignMesh.h"
#include "ContainersAndTypes.h"
#include "Editor.h"
#include "Editor/UnrealEd/Classes/Editor/EditorEngine.h"
#include "LightingBuildOptions.h"
#include <stack>
#include <memory>

//forward declarations

class UfileParser : public IFastXmlCallback
{
public:
	UfileParser(const TCHAR*);
	virtual ~UfileParser();

	//before starting any parsing.
	void destroyFoundActors();

	//IFastXMLCallback
	bool ProcessXmlDeclaration(const TCHAR* ElementData, int32 XmlFileLineNumber);
	bool ProcessElement(const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber);
	bool ProcessAttribute(const TCHAR* AttributeName, const TCHAR* AttributeValue);
	bool ProcessClose(const TCHAR* Element);
	bool ProcessComment(const TCHAR* Comment);
	bool loadxml();

	//Put the shape coordinates into Shapecoordinates vector
	void ShapeProcessing(const TCHAR*);

	//----Functions for initializing the node objects----

	//Collect all required node attributes for one object as member variables and then initialize a node object
	void InitializeNodeAttributes(const TCHAR*, const TCHAR*);
	SimpleNodePtr InitializeNode();

	//one container object to store all node mappings
	NodeCont NodeContainer;		

	//Getter and setter methods of temporary node ID for the latest node created
	FString getTempNodeID();
	bool setTempNodeID(const TCHAR*);

	//To find all actors that are of the types AEdgeMesh, AAtmosphericFog and ASkyLight types. 
	void getAllActorsOfClass();

	//----Functions for initializing the walkingArea objects----

	//Collect all required node attributes for one object as member variables and then initialize a node object
	void InitializeWalkingAreaAttributes(const TCHAR*, const TCHAR*);
	void InitializewalkingArea();

	//one container object to store all node mappings
	walkingAreaCont walkingAreaContainer;

	//----Functions for initializing the edge objects----
	//Collect all the required internal edge attributes (specifically for splines which are within a junction)
	void InitializeInternalEdgeAttributes(const TCHAR*, const TCHAR*);
	void MakeSpline(std::vector<float>&, FVector&);
	void MakeSpline(std::vector<float>&);

	//Collect all the required edge attributes for one object as member variables and then initialize a edge object
	void InitializeEdgeAttributes(const TCHAR*, const TCHAR*);
	SimpleEdgePtr InitializeEdge(const TCHAR*);
	SimpleEdgePtr InitializePedestrianEdge();

	//Container object for edge mappings
	EdgeCont EdgeContainer;

	//To calculate Lane width
	//void calculateLaneWidth();
	float laneWidth;

	//----------------Functions for initialzing Traffic Lights and Stop signs----------------
	void InitializetrafficLightAttributes(const TCHAR*, const TCHAR*); //Traffic light id is currently being used to place stop signs also.
	void InitializeTrafficControl(const TCHAR*);  //Used for either initializing traffic lights and stop signs.
	void iterateWalkingAreas();

private:
	UWorld* World = GEditor->GetEditorWorldContext().World();
	std::vector<float> Shapecoordinates;
	FString selectedXMLFile;
	TArray<AActor*> FoundActors;
	FLightingBuildOptions LightOptions;

	//node related flags and member variables
	bool isElementNode = false;//flag
	bool isPriorityNode = false;
	bool isTrafficNode = false;
	const TCHAR* nodeXCoordinate;//attribute
	const TCHAR* nodeYCoordinate;
	bool xCoordinateIsSet = false;
	bool yCoordinateIsSet = false;
	bool laneWidthIsSet = false;
	TArray<TUniquePtr<FString>> trafficControlIDList; //List of node IDs which are of traffic light or stop sign type. 

	//edge flags and temp member variables
	bool isInternalEdge = false;
	bool isElementEdge = false;
	FString fromNode = "";
	FString toNode = "";
	FString laneLength = "";
	bool fromNodeSet = false;
	bool toNodeSet = false;
	bool lengthIsSet = false;
	
	void resetFlagsAndTempMembers();
	bool shapeIsSet = false;

	//lane parameters
	bool isElementLane = false;

	//walking area member variables
	bool isWalkingArea = false;
	bool doesWalkingAreaExist = false; //useful when trying to spawn the traffic light.

	//pedestrian crossing member variables
	bool isCrossing = false;

	//sidewalk member variables
	bool isSidewalk = false;

	//traffic light member variables
	bool isElementtrafficLight = false;

	//temporary ID
	FString tempNodeID = "";
	FString tempEdgeID = "";
	FString walkingAreaID = "";
	FString walkingAreaKeyID = "";
	FString tempTrafficLightID = "";
};
