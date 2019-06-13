#include "fileParser.h"
#include "EngineMinimal.h"
#include "Runtime/XmlParser/Public/FastXml.h"
#include "Runtime/XmlParser/Public/XmlParser.h"
#include "Engine.h"
#include "SimpleNode.h"
#include "walkingArea.h"
#include "Editor.h"
#include "Editor/UnrealEd/Classes/Editor/EditorEngine.h"
#include <cstdlib>
#include <sstream>
#include <memory>


UfileParser::UfileParser(const TCHAR* selectedFile) : selectedXMLFile(selectedFile)
{
	UWorld* World = GEditor->GetEditorWorldContext().World();
	FVector Location = FVector(0.0f, 0.0f, 2000.0f);
	FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnParameters;
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(World, AEdgeMesh::StaticClass(), FoundActors);
	for (int i = 0; i < FoundActors.Num(); i++) {
		World->DestroyActor(FoundActors[i]); //Destroy all actors before starting
	}
	World->SpawnActor<AAtmosphericFog>(Location, Rotation, SpawnParameters);
	//World->SpawnActor<ADirectionalLight>(Location, Rotation, SpawnParameters);
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
		if (isElementLane == true)
		{
			ShapeProcessing(AttributeValue);
			shapeIsSet = true;
		}
		return;
	}

	else if (FString(AttributeName).Equals(TEXT("width")))
	{
		laneWidth = FCString::Atof(AttributeValue);
		laneWidthIsSet = true;
	}

	else if (FString(AttributeName).Equals(TEXT("allow")))
	{
		isSidewalk = true;
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

void UfileParser::InitializeWalkingAreaAttributes(const TCHAR* AttributeName, const TCHAR* AttributeValue)
{
	if (FString(AttributeName).Equals(TEXT("id")))
	{
		walkingAreaID = FString(AttributeValue);
		return;
	}

	if ((FString(AttributeName)).Equals(TEXT("shape")))
	{
		ShapeProcessing(AttributeValue);
		shapeIsSet = true;
		return;
	}

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

	UE_LOG(LogEngine, Warning, TEXT("Node Attributes initialized!"));

}

//walking Area parsing is similar to the nodes. TMap storing the walkingArea objects is different. Also walkingArea meshes will be 
//3d at some point. 
walkingAreaPtr UfileParser::InitializewalkingArea()
{
	//unique_ptr for object creation for extended lifetime
	walkingAreaPtr currentWalkingArea = std::make_unique<walkingArea>();
	currentWalkingArea->walkingAreaShapeCoordinates = Shapecoordinates;
	currentWalkingArea->setWalkingAreaID(*walkingAreaID);

	//initialize map with the pointer for extended walkingArea lifetime
	walkingAreaContainer.walkingAreaMap.Add(*walkingAreaID, currentWalkingArea.get());

	FQuat RotationEdge(0.0f, 0.0f, 0.0f, 0.0f);
	currentWalkingArea->centroidCalculation();
	FVector origin(currentWalkingArea->centroidX, currentWalkingArea->centroidY, 0.1f);
	UWorld* World = GEditor->GetEditorWorldContext().World();


	FTransform SpawnTransform(RotationEdge, origin);
	AEdgeMesh* MyDeferredActor = Cast<AEdgeMesh>(UGameplayStatics::BeginDeferredActorSpawnFromClass(World, AEdgeMesh::StaticClass(), SpawnTransform)); //Downcasting

	if (MyDeferredActor)
	{
		FVector coordinates;
		int i = 0;
		while ((i + 2) <= currentWalkingArea->walkingAreaShapeCoordinates.size())
		{

			coordinates.X = currentWalkingArea->walkingAreaShapeCoordinates[i] - currentWalkingArea->centroidX;
			coordinates.Y = currentWalkingArea->walkingAreaShapeCoordinates[i + 1] - currentWalkingArea->centroidY;
			coordinates.Z = 0.0f;
			MyDeferredActor->vertices.Add(coordinates);
			i += 2;
		}

		for (int i = 0; i < (MyDeferredActor->vertices.Num()); i++) {
			UE_LOG(LogEngine, Warning, TEXT("MyDeferredActor->vertices[%d]: "), i);
			UE_LOG(LogEngine, Warning, TEXT("FVectorX: %f"), MyDeferredActor->vertices[i].X);
			UE_LOG(LogEngine, Warning, TEXT("FVectorY: %f"), MyDeferredActor->vertices[i].Y);
			UE_LOG(LogEngine, Warning, TEXT("FVectorZ: %f"), MyDeferredActor->vertices[i].Z);
			UE_LOG(LogEngine, Warning, TEXT("====="));
		}

		UGameplayStatics::FinishSpawningActor(MyDeferredActor, SpawnTransform);
		//MyDeferredActor->FinishSpawning(SpawnLocAndRotation);

		UE_LOG(LogEngine, Warning, TEXT("the walkingArea actor is spawned"));
	}
	return currentWalkingArea;
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

SimpleEdgePtr UfileParser::InitializePedestrianEdge()
{
	//unique_ptr for object creation for extended lifetime
	SimpleEdgePtr Edge = std::make_unique<SimpleEdge>();
	Edge->SetID(*tempEdgeID);
	Edge->setFromID(*fromNode);
	Edge->setToID(*toNode);
	Edge->setLaneLength(*laneLength);

	//initialize map with the pointer for extended node lifetime
	EdgeContainer.EdgeMap.Add(*tempEdgeID, Edge.get());
	int i = 0;
	std::vector<float> tempvector;
	while ((i + 3) <= (Shapecoordinates.size() - 1))
	{
		tempvector.push_back(Shapecoordinates[i]);
		tempvector.push_back(Shapecoordinates[i + 1]);
		tempvector.push_back(Shapecoordinates[i + 2]);
		tempvector.push_back(Shapecoordinates[i + 3]);

		Edge->setShapeCoordinates(tempvector);
		tempvector.clear();

		if (laneWidthIsSet == true)
		{
			Edge->setSideWalkVertCoordinates(laneWidth);  //default SUMO lane width
		}
		else
		{
			Edge->setSideWalkVertCoordinates(3.2);  //default SUMO lane width
		}

		FVector originCoordinates = Edge->centroid;
		FQuat RotationEdge(0.0f, 0.0f, 0.0f, 0.0f);
		FVector origin(0.0f, 0.0f, 0.0f);
		
		origin.X = originCoordinates.X;
		origin.Y = originCoordinates.Y;
		origin.Z = 0.2f;
		

		UWorld* World = GEditor->GetEditorWorldContext().World();

		FTransform SpawnTransform(RotationEdge, origin);
		AEdgeMesh* MyDeferredActor = Cast<AEdgeMesh>(UGameplayStatics::BeginDeferredActorSpawnFromClass(World, AEdgeMesh::StaticClass(), SpawnTransform)); //Downcasting

		if (MyDeferredActor)

		{
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

			UE_LOG(LogEngine, Warning, TEXT("==============pedestrian actor is spawned!==========="));
		}

		FVector originCoordinatesCurb1 = Edge->CentroidcurbTop1;
		FQuat RotationEdgeCurb1(0.0f, 0.0f, 0.0f, 0.0f);
		FVector originCurb1(0.0f, 0.0f, 0.0f);

		originCurb1.X = originCoordinatesCurb1.X;
		originCurb1.Y = originCoordinatesCurb1.Y;
		originCurb1.Z = 0.2f;

		FTransform SpawnTransformCurb1(RotationEdgeCurb1, originCurb1);
		AEdgeMesh* MyDeferredActor1 = Cast<AEdgeMesh>(UGameplayStatics::BeginDeferredActorSpawnFromClass(World, AEdgeMesh::StaticClass(), SpawnTransformCurb1)); //Downcasting

		if (MyDeferredActor1)

		{
			(MyDeferredActor1->vertices) = (Edge->curbVerticesTop1);

			for (int i = 0; i < (MyDeferredActor1->vertices.Num()); i++) {
				UE_LOG(LogEngine, Warning, TEXT("MyDeferredActor->vertices[%d]: "), i);
				UE_LOG(LogEngine, Warning, TEXT("FVectorX: %f"), MyDeferredActor1->vertices[i].X);
				UE_LOG(LogEngine, Warning, TEXT("FVectorY: %f"), MyDeferredActor1->vertices[i].Y);
				UE_LOG(LogEngine, Warning, TEXT("FVectorZ: %f"), MyDeferredActor1->vertices[i].Z);
				UE_LOG(LogEngine, Warning, TEXT("====="));
			}

			UGameplayStatics::FinishSpawningActor(MyDeferredActor1, SpawnTransformCurb1);
			//MyDeferredActor->FinishSpawning(SpawnLocAndRotation);

			UE_LOG(LogEngine, Warning, TEXT("==============the curb actor 1 is spawned=============="));
		}

		FVector originCoordinatesCurb2 = Edge->CentroidcurbTop2;
		FQuat RotationEdgeCurb2(0.0f, 0.0f, 0.0f, 0.0f);
		FVector originCurb2(0.0f, 0.0f, 0.0f);

		originCurb2.X = originCoordinatesCurb2.X;
		originCurb2.Y = originCoordinatesCurb2.Y;
		originCurb2.Z = 0.2f;

		FTransform SpawnTransformCurb2(RotationEdgeCurb2, originCurb2);
		AEdgeMesh* MyDeferredActor2 = Cast<AEdgeMesh>(UGameplayStatics::BeginDeferredActorSpawnFromClass(World, AEdgeMesh::StaticClass(), SpawnTransformCurb2)); //Downcasting

		if (MyDeferredActor2)

		{
			(MyDeferredActor2->vertices) = (Edge->curbVerticesTop2);

			for (int i = 0; i < (MyDeferredActor2->vertices.Num()); i++) {
				UE_LOG(LogEngine, Warning, TEXT("MyDeferredActor->vertices[%d]: "), i);
				UE_LOG(LogEngine, Warning, TEXT("FVectorX: %f"), MyDeferredActor2->vertices[i].X);
				UE_LOG(LogEngine, Warning, TEXT("FVectorY: %f"), MyDeferredActor2->vertices[i].Y);
				UE_LOG(LogEngine, Warning, TEXT("FVectorZ: %f"), MyDeferredActor2->vertices[i].Z);
				UE_LOG(LogEngine, Warning, TEXT("====="));
			}

			UGameplayStatics::FinishSpawningActor(MyDeferredActor2, SpawnTransformCurb2);
			//MyDeferredActor->FinishSpawning(SpawnLocAndRotation);

			UE_LOG(LogEngine, Warning, TEXT("=================the curbcurbcurb actor 2 is spawned==========="));
		}

		i += 2;
	}
	return Edge;
}

SimpleEdgePtr UfileParser::InitializeEdge(const TCHAR* edgeType)
{
	//unique_ptr for object creation for extended lifetime
	SimpleEdgePtr Edge = std::make_unique<SimpleEdge>();
	Edge->SetID(*tempEdgeID);
	Edge->setFromID(*fromNode);
	Edge->setToID(*toNode);
	Edge->setLaneLength(*laneLength);

	//initialize map with the pointer for extended node lifetime
	EdgeContainer.EdgeMap.Add(*tempEdgeID, Edge.get());
	int i = 0;
	std::vector<float> tempvector;
	while ((i + 3) <= (Shapecoordinates.size() - 1))
	{
		tempvector.push_back(Shapecoordinates[i]);
		tempvector.push_back(Shapecoordinates[i+1]);
		tempvector.push_back(Shapecoordinates[i+2]);
		tempvector.push_back(Shapecoordinates[i+3]);

		Edge->setShapeCoordinates(tempvector);
		tempvector.clear();

		if (laneWidthIsSet == true)
		{
			Edge->setVertexCoordinates(laneWidth);  //default SUMO lane width
		}
		else
		{
			Edge->setVertexCoordinates(3.2);  //default SUMO lane width
		}

		FVector originCoordinates = Edge->centroid;
		FQuat RotationEdge(0.0f, 0.0f, 0.0f, 0.0f);
		FVector origin(0.0f, 0.0f, 0.0f);
		if (FString(edgeType).Equals(TEXT("standard")))
		{
			origin.X = originCoordinates.X;
			origin.Y = originCoordinates.Y;
			origin.Z = originCoordinates.Z;
		}
		else if (FString(edgeType).Equals(TEXT("crossing")))
		{
			origin.X = originCoordinates.X;
			origin.Y = originCoordinates.Y;
			origin.Z = 0.1f;
		}
		else if (FString(edgeType).Equals(TEXT("sidewalk")))
		{
			origin.X = originCoordinates.X;
			origin.Y = originCoordinates.Y;
			origin.Z = 0.2f;
		}

		UWorld* World = GEditor->GetEditorWorldContext().World();

		FTransform SpawnTransform(RotationEdge, origin);
		AEdgeMesh* MyDeferredActor = Cast<AEdgeMesh>(UGameplayStatics::BeginDeferredActorSpawnFromClass(World, AEdgeMesh::StaticClass(), SpawnTransform)); //Downcasting

		if (MyDeferredActor)

		{
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

		i+=2;
	}
	return Edge;
}

bool UfileParser::loadxml()
{
	UE_LOG(LogEngine, Warning, TEXT("Loading started"));
	FText outError;
	int32 outErrorNum;
	FString Text = "";
	bool success = FFastXml::ParseXmlFile((IFastXmlCallback*)(this), selectedXMLFile.GetCharArray().GetData(), (TCHAR*)*Text, nullptr, false, false, outError, outErrorNum);
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
	else if ((FString(ElementName)).Equals(TEXT("lane")))
	{
		isElementLane = true;
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
			UE_LOG(LogEngine, Warning, TEXT("Node object created!"));
		}
	}
	else if ((isElementEdge == true) || (isElementLane == true))
	{
		InitializeEdgeAttributes(AttributeName, AttributeValue);
	}

	if (FString(AttributeValue).Equals(TEXT("walkingarea")))
	{
		isWalkingArea = true;
	}
	if (isWalkingArea == true)
	{
		UE_LOG(LogEngine, Warning, TEXT("walking area true"));
		InitializeWalkingAreaAttributes(AttributeName, AttributeValue);
	}

	if (FString(AttributeValue).Equals(TEXT("crossing")))
	{
		isCrossing = true;
	}
	if (isCrossing == true)
	{
		UE_LOG(LogEngine, Warning, TEXT("crossing is true"));
		InitializeEdgeAttributes(AttributeName, AttributeValue);
	}
	
	return true;
}

bool UfileParser::ProcessClose(const TCHAR* Element)
{
	if ((fromNodeSet == true) && (toNodeSet == true) && (lengthIsSet == true) && (shapeIsSet == true))
	{
		if (isSidewalk == true)
		{
			InitializePedestrianEdge();
		}
		else
		{
			InitializeEdge(TEXT("standard"));
		}
		//UE_LOG(LogEngine, Warning, TEXT("Edge object created!")); 
	}
	else if ((isCrossing == true) && (shapeIsSet == true))
	{
		InitializeEdge(TEXT("crossing"));
	}
	if (((FString(Element)).Equals(TEXT("lane"))))
	{
		if (isWalkingArea == false)
		{
			Shapecoordinates.clear();
			shapeIsSet = false;
			lengthIsSet = false;
			isElementLane = false;
			laneWidthIsSet = false;
			isCrossing = false;
			isSidewalk = false;
		}
		else
		{
			if (shapeIsSet)
			{
				UE_LOG(LogEngine, Warning, TEXT("Walking area shape is set"))
				InitializewalkingArea();
				UE_LOG(LogEngine, Warning, TEXT("WalkingArea created"));
				isWalkingArea = false;
				shapeIsSet = false;
			}
		}
	}
	else
	{
		resetFlagsAndTempMembers();
	}
	//UE_LOG(LogEngine, Warning, TEXT("ProcessClose Element %s"), Element);
	return true;
}

bool UfileParser::ProcessComment(const TCHAR* Comment)
{
	//UE_LOG(LogEngine, Warning, TEXT("ProcessComment Comment: %s"), Comment);
	return true;
}









