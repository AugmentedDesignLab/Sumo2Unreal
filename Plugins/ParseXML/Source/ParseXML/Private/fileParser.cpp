#include "fileParser.h"
#include "Runtime/XmlParser/Public/FastXml.h"
#include "Runtime/XmlParser/Public/XmlParser.h"
#include "Engine.h"
#include "SimpleNode.h"
#include "Editor.h"
#include "Editor/UnrealEd/Classes/Editor/EditorEngine.h"

#include <sstream>
#include <memory>



UfileParser::UfileParser(const TCHAR* selectedFile) : selectedXMLFile(selectedFile)
{

}

UfileParser::~UfileParser()
{

}

void UfileParser::InitializeEdgeAttributes(const TCHAR* AttributeName, const TCHAR* AttributeValue) 
{
	if (FString(AttributeName).Equals(TEXT("id")))
	{
		tempEdgeID = FString(AttributeValue);
		return;
	}

	else if (FString(AttributeName).Equals(TEXT("from")))
	{
		fromNode = FString(AttributeValue);
		fromNodeSet = true;
		return;
	}

	else if (FString(AttributeName).Equals(TEXT("to")))
	{
		toNode = FString(AttributeValue);
		toNodeSet = true;
		return;
	}

	else if (FString(AttributeName).Equals(TEXT("length")))
	{
		laneLength = FString(AttributeValue);
		lengthIsSet = true;
		return;
	}

	else if (FString(AttributeName).Equals(TEXT("shape")))
	{
		ShapeProcessing(AttributeValue);
		shapeIsSet = true;
		return;
	}
	else
	{
		return;
	}

	//UE_LOG(LogEngine, Warning, TEXT("Edge Attributes initialized!"));
	
}

FString UfileParser::getTempNodeID()
{
	return tempNodeID;
}

bool UfileParser::setTempNodeID(const TCHAR* tempTempNodeID)
{
	tempNodeID = FString(tempTempNodeID);
	return (tempNodeID.IsEmpty());

}

void UfileParser::ShapeProcessing(const TCHAR* ShapeString)
{
	std::string CoordinateString = TCHAR_TO_UTF8(ShapeString);
	Shapecoordinates.clear();
	for (std::string::iterator it = CoordinateString.begin(); it != CoordinateString.end(); ++it) 
	{
		if (*it == ',') 
		{
			*it = ' ';
		}
		else continue;			//convert all commas in string stream into space
	}
	
	std::stringstream ss;
	ss << CoordinateString;

	float found;

	while (!ss.eof()) 
	{
		//check if it is valid to put stringstream object into float variable
		if (ss >> found)
		{
			Shapecoordinates.push_back(found);
		}
	}
}

void UfileParser::resetFlagsAndTempMembers()
{
	//isElementNode = false;
	isPriorityNode = false;
	tempNodeID = "";
	nodeXCoordinate = nullptr;
	nodeYCoordinate = nullptr;
	Shapecoordinates.clear();
	xCoordinateIsSet = false;
	yCoordinateIsSet = false;
	shapeIsSet = false;

	//isElementEdge = false;
	tempEdgeID = "";
	fromNode = "";
	toNode = "";
	laneLength = "";
	fromNodeSet = false;
	toNodeSet = false;
	lengthIsSet = false;
}

void UfileParser::InitializeNodeAttributes(const TCHAR* AttributeName, const TCHAR* AttributeValue)
{

	if (FString(AttributeName).Equals(TEXT("id")))
	{
		setTempNodeID(AttributeValue);
		return;
	}

	if (((FString(AttributeValue)).Equals(TEXT("priority"))))
	{
		isPriorityNode = true;
		return;
	}

	//Set temp node positions
	if ((isPriorityNode == true) && ((FString(AttributeName)).Equals(TEXT("x"))))
	{
		nodeXCoordinate = AttributeValue;
		xCoordinateIsSet = true;
		return;
	}

	else if ((isPriorityNode == true) && ((FString(AttributeName)).Equals(TEXT("y"))))
	{
		nodeYCoordinate = AttributeValue;
		yCoordinateIsSet = true;
		return;
	}

	else if ((isPriorityNode == true) && ((FString(AttributeName)).Equals(TEXT("shape"))))
	{
		ShapeProcessing(AttributeValue);
		shapeIsSet = true;
		return;
	}

	else
	{
		return;
	}

	//UE_LOG(LogEngine, Warning, TEXT("Node Attributes initialized!"));

}

SimpleNodePtr UfileParser::InitializeNode()
{
	//unique_ptr for object creation for extended lifetime
	SimpleNodePtr Node = std::make_unique<SimpleNode>();
	Node->SetID(*tempNodeID);
	Node->nodeShapecoordinates = Shapecoordinates;
	Node->SetPosition(nodeXCoordinate, nodeYCoordinate);

	//initialize map with the pointer for extended node lifetime
	NodeContainer.NodeMap.Add(*tempNodeID, Node.get());

	FQuat RotationEdge(0.0f, 0.0f, 0.0f, 0.0f);
	FVector origin(Node->NodePosition.X, Node->NodePosition.Y, 0.0f);
	UWorld* World = GEditor->GetEditorWorldContext().World();

	FTransform SpawnTransform(RotationEdge, origin);
	AEdgeMesh* MyDeferredActor = Cast<AEdgeMesh>(UGameplayStatics::BeginDeferredActorSpawnFromClass(World, AEdgeMesh::StaticClass(), SpawnTransform)); //Downcasting

	if (MyDeferredActor)

	{
		FVector coordinates;
		int i=0;
		while ((i+2) <= Node->nodeShapecoordinates.size())
		{
				
				coordinates.X = Node->nodeShapecoordinates[i] - Node->NodePosition.X;
				coordinates.Y = Node->nodeShapecoordinates[i + 1] - Node->NodePosition.Y;
				coordinates.Z = 0.0f;
				MyDeferredActor->vertices.Add(coordinates);	
				i += 2;
		}
		/*
		for (int i = 0; i < (Node->vertexAnglesSorted).Num(); i++) //find the corresponding index of the sorted angle to the unsorted angle vertex
		{
			UE_LOG(LogEngine, Warning, TEXT("The sorted angle is %f"), (Node->vertexAnglesSorted[i]));
			for (int j = 0; j < (Node->vertexAnglesUnSorted).Num(); j++)
			{
				if ((Node->vertexAnglesUnSorted[j]) == (Node->vertexAnglesSorted[i]))
				{
					UE_LOG(LogEngine, Warning, TEXT("This corresponds to vertex %d"), (j + 1));
					(MyDeferredActor->vertices).Add(Node->vertexArray[j]);
				}

			}
		}
		*/

		for (int i = 0; i < (MyDeferredActor->vertices.Num()); i++) {
			UE_LOG(LogEngine, Warning, TEXT("MyDeferredActor->vertices[%d]: "), i);
			UE_LOG(LogEngine, Warning, TEXT("FVectorX: %f"), MyDeferredActor->vertices[i].X);
			UE_LOG(LogEngine, Warning, TEXT("FVectorY: %f"), MyDeferredActor->vertices[i].Y);
			UE_LOG(LogEngine, Warning, TEXT("FVectorZ: %f"), MyDeferredActor->vertices[i].Z);
			UE_LOG(LogEngine, Warning, TEXT("====="));
		}

		UGameplayStatics::FinishSpawningActor(MyDeferredActor, SpawnTransform);
		//MyDeferredActor->FinishSpawning(SpawnLocAndRotation);

		UE_LOG(LogEngine, Warning, TEXT("the Node actor is spawned"));
	}
	return Node;
}

SimpleEdgePtr UfileParser::InitializeEdge()
{
	//unique_ptr for object creation for extended lifetime
	SimpleEdgePtr Edge = std::make_unique<SimpleEdge>();
	Edge->SetID(*tempEdgeID);
	Edge->setShapeCoordinates(Shapecoordinates);
	Edge->setFromID(*fromNode);
	Edge->setToID(*toNode);
	Edge->setLaneLength(*laneLength);
	//initialize map with the pointer for extended node lifetime
	EdgeContainer.EdgeMap.Add(*tempEdgeID, Edge.get());
	//calculateLaneWidth();
	Edge->setVertexCoordinates(3.2);
	FVector originCoordinates = Edge->centroid;

	FQuat RotationEdge(0.0f, 0.0f, 0.0f, 0.0f);
	FVector origin(originCoordinates.X, originCoordinates.Y, originCoordinates.Z);
	UWorld* World = GEditor->GetEditorWorldContext().World();

	FTransform SpawnTransform(RotationEdge, origin);
	AEdgeMesh* MyDeferredActor = Cast<AEdgeMesh>(UGameplayStatics::BeginDeferredActorSpawnFromClass(World, AEdgeMesh::StaticClass(), SpawnTransform)); //Downcasting
	
	if (MyDeferredActor)

	{
		/*
		for (int i = 0; i < (Edge->vertexAnglesSorted).Num(); i++) //find the corresponding index of the sorted angle to the unsorted angle vertex
		{
			UE_LOG(LogEngine, Warning, TEXT("The sorted angle is %f"),(Edge->vertexAnglesSorted[i]));
			for (int j = 0; j < (Edge->vertexAnglesUnSorted).Num(); j++)
			{
				if ((Edge->vertexAnglesUnSorted[j]) == (Edge->vertexAnglesSorted[i]))
				{
					UE_LOG(LogEngine, Warning, TEXT("This corresponds to vertex %d"), (j + 1));
					(MyDeferredActor->vertices).Add(Edge->vertexArray[j]);
				}

			}
		}
		*/

		(MyDeferredActor->vertices) = (Edge->vertexArray);

		for (int i = 0; i < (MyDeferredActor->vertices.Num()); i++) {
			UE_LOG(LogEngine, Warning, TEXT("MyDeferredActor->vertices[%d]: "), i);
			UE_LOG(LogEngine, Warning, TEXT("FVectorX: %f"), MyDeferredActor->vertices[i].X);
			UE_LOG(LogEngine, Warning, TEXT("FVectorY: %f"), MyDeferredActor->vertices[i].Y);
			UE_LOG(LogEngine, Warning, TEXT("FVectorZ: %f"), MyDeferredActor->vertices[i].Z);
			UE_LOG(LogEngine, Warning, TEXT("====="));
		}

		UGameplayStatics::FinishSpawningActor(MyDeferredActor, SpawnTransform);
		//MyDeferredActor->FinishSpawning(SpawnLocAndRotation);

		UE_LOG(LogEngine, Warning, TEXT("the edge actor is spawned"));
	}
	return Edge;
}

void UfileParser::calculateLaneWidth()
{
	FVector nearestJunctionPoint(0.0f, 0.0f, 0.0f);

	for (auto& Elem : EdgeContainer.EdgeMap)
	{
		float edgeShapeX0 = Elem.Value->edgeShapeCoordinates[1];
		float edgeShapeY0 = Elem.Value->edgeShapeCoordinates[2];
		
		for (auto& ElemNode : NodeContainer.NodeMap)
		{
			if ((ElemNode.Value->ID).Equals(Elem.Value->fromID))
			{
				int i = 1;
				float nearestJunctionX = 0;
				while (i < ElemNode.Value->nodeShapecoordinates.size())
				{
					nearestJunctionX = std::abs(ElemNode.Value->nodeShapecoordinates[i] - edgeShapeX0);
					if (nearestJunctionX <= nearestJunctionPoint.X)
					{
						nearestJunctionPoint.X = nearestJunctionX;
					}
					i += 2;
				}
				i = 2;
				float nearestJunctionY = 0;
				while (i < ElemNode.Value->nodeShapecoordinates.size())
				{
					nearestJunctionY = std::abs(ElemNode.Value->nodeShapecoordinates[i] - edgeShapeY0);
					if (nearestJunctionY <= nearestJunctionPoint.Y)
					{
						nearestJunctionPoint.Y = nearestJunctionY;
					}
					i += 2;
				}
				if (nearestJunctionX && nearestJunctionY)
				{
					laneWidth = std::sqrt(std::pow(nearestJunctionX, 2) + std::pow(nearestJunctionY, 2));
				}

			}
		}
	}
}

bool UfileParser::loadxml()
{
	UE_LOG(LogEngine, Warning, TEXT("Loading started"));
	FText outError;
	int32 outErrorNum;
	bool success = FFastXml::ParseXmlFile((IFastXmlCallback*)(this), selectedXMLFile.GetCharArray().GetData(), TEXT(""), nullptr, false, false, outError, outErrorNum);
	return success;
}

bool UfileParser::ProcessXmlDeclaration(const TCHAR* ElementData, int32 XmlFileLineNumber)
{
	UE_LOG(LogEngine, Warning, TEXT("ProcessXmlDeclaration ElementData: %s, XmlFileLineNumber: %f"), ElementData, XmlFileLineNumber);
	return true;
}

bool UfileParser::ProcessElement(const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber)
{
	if ((FString(ElementName)).Equals(TEXT("junction")))
	{
		isElementNode = true;
		isElementEdge = false;
	}
	else if ((FString(ElementName)).Equals(TEXT("edge")))
	{
		isElementEdge = true;
		isElementNode = false;
	}
	else
	{
		isElementNode = false;
	}

	//UE_LOG(LogEngine, Warning, TEXT("ProcessElement ElementName: %s, ElementValue: %s"), ElementName, ElementData);
	return true;
}

bool UfileParser::ProcessAttribute(const TCHAR* AttributeName, const TCHAR* AttributeValue)
{
	//UE_LOG(LogEngine, Warning, TEXT("ProcessAttribute AttributeName: %s, AttributeValue: %s"), AttributeName, AttributeValue);

	if (isElementNode == true)
	{
		InitializeNodeAttributes(AttributeName, AttributeValue);
		if ((shapeIsSet == true) && (xCoordinateIsSet == true) && (yCoordinateIsSet == true))
		{
			InitializeNode();
			//UE_LOG(LogEngine, Warning, TEXT("Node object created!"));
		}
		
	}
	else if (isElementEdge == true) 
	{
		InitializeEdgeAttributes(AttributeName, AttributeValue);
		if ((fromNodeSet == true) && (toNodeSet == true) && (lengthIsSet == true) && (shapeIsSet == true))
		{
			InitializeEdge();
			//UE_LOG(LogEngine, Warning, TEXT("Edge object created!")); 
		}

	}
	
	return true;
}

bool UfileParser::ProcessClose(const TCHAR* Element)
{
	resetFlagsAndTempMembers();
	//UE_LOG(LogEngine, Warning, TEXT("ProcessClose Element %s"), Element);
	return true;
}

bool UfileParser::ProcessComment(const TCHAR* Comment)
{
	//UE_LOG(LogEngine, Warning, TEXT("ProcessComment Comment: %s"), Comment);
	return true;
}









