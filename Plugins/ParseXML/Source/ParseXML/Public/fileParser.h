#pragma once
#include "Runtime/XmlParser/Public/FastXml.h"
#include "Runtime/XmlParser/Public/XmlParser.h"
#include "Runtime/Core/Public/Containers/Map.h"
#include "SimpleEdge.h"

#include "ContainersAndTypes.h"

#include <stack>
#include <memory>

//class declarations
class SimpleNode;

class UfileParser : public IFastXmlCallback
{
public:
	UfileParser();
	~UfileParser();

	//IFastXMLCallback
	bool ProcessXmlDeclaration(const TCHAR* ElementData, int32 XmlFileLineNumber);
	bool ProcessElement(const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber);
	bool ProcessAttribute(const TCHAR* AttributeName, const TCHAR* AttributeValue);
	bool ProcessClose(const TCHAR* Element);
	bool ProcessComment(const TCHAR* Comment);
	bool loadxml();

	//Put the shape coordinates into Shapecoordinates vector
	void ShapeProcessing(const TCHAR*);

	//Collect all required node attributes for one object as member variables and then initialize a node object
	void InitializeNodeAttributes(const TCHAR*, const TCHAR*);
	SimpleNodePtr InitializeNode();
	NodeCont NodeContainer;		//one container object to store all node mappings

	//Getter and setter methods of temporary node ID for the latest node created
	FString getTempNodeID();
	bool setTempNodeID(const TCHAR*);

	//parses through edgelist and prints all edges
	void printEdges();

	//adds attributes to edge
	void InitializeEdgeAttributes(const TCHAR* AttributeName, const TCHAR* AttributeValue);

	//adds edges to the edge list
	void addEdge(const TCHAR* Element);

private:
	std::vector<float> Shapecoordinates;

	//node flags and temp member variables
	bool isElementNode = false;
	bool isPriorityNode = false;
	bool shapeIsSet = false;
	const TCHAR* nodeXCoordinate;
	const TCHAR* nodeYCoordinate;
	bool xCoordinateIsSet = false;
	bool yCoordinateIsSet = false;


	//edge flags and member variables
	SimpleEdge edgeHolder;
	TMap<FString, SimpleEdge> EdgeList;
	bool isElementEdge = false;
	
	void resetFlagsAndTempMembers();

	//temporary ID
	FString tempNodeID = "";
};
