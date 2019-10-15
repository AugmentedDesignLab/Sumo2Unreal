#include "fileParser.h"
#include "EngineMinimal.h"
#include "Runtime/XmlParser/Public/FastXml.h"
#include "Runtime/XmlParser/Public/XmlParser.h"
#include "WayPoint.h"
#include "Engine.h"
#include <cstdlib>
#include <sstream>
#include <memory>


UfileParser::UfileParser(const TCHAR* selectedFile) : selectedXMLFile(selectedFile)
{
	FVector Location = FVector(0.0f, 0.0f, 2000.0f);
	FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnParameters;
	getAllActorsOfClass();
	World->SpawnActor<AAtmosphericFog>(Location, Rotation, SpawnParameters);
	Location.Z = 100000.0f;
	ASkyLight* Skylight = World->SpawnActor<ASkyLight>(Location, Rotation, SpawnParameters);
	if (Skylight !=nullptr) {
		Skylight->GetLightComponent()->SetIntensity(5.0f);
		GEditor->BuildLighting(LightOptions);
	}
}

UfileParser::~UfileParser()
{
	
}

bool UfileParser::ProcessXmlDeclaration(const TCHAR* ElementData, int32 XmlFileLineNumber) { return true; };

void UfileParser::destroyFoundActors() {
	for (int i = 0; i < FoundActors.Num(); i++) {
		World->DestroyActor(FoundActors[i]); //Destroy all actors before starting
	}
}

void UfileParser::getAllActorsOfClass() {
	UGameplayStatics::GetAllActorsOfClass(World, ARoadMesh::StaticClass(), FoundActors);
	destroyFoundActors();
	UGameplayStatics::GetAllActorsOfClass(World, AAtmosphericFog::StaticClass(), FoundActors);
	destroyFoundActors();
	UGameplayStatics::GetAllActorsOfClass(World, ASkyLight::StaticClass(), FoundActors);
	destroyFoundActors();
	UGameplayStatics::GetAllActorsOfClass(World, AStopSignMesh::StaticClass(), FoundActors);
	destroyFoundActors();
}

FString UfileParser::getTempNodeID() {
	return tempNodeID;
}

bool UfileParser::setTempNodeID(const TCHAR* tempTempNodeID) {
	tempNodeID = FString(tempTempNodeID);
	return (tempNodeID.IsEmpty());
}

void UfileParser::ShapeProcessing(const TCHAR* ShapeString) {
	std::string CoordinateString = TCHAR_TO_UTF8(ShapeString);
	Shapecoordinates.clear();
	for (std::string::iterator it = CoordinateString.begin(); it != CoordinateString.end(); ++it) {
		if (*it == ',') {
			*it = ' ';
		}
		else continue;			//convert all commas in string stream into space
	}

	std::stringstream ss;
	ss << CoordinateString;

	float found;
	int i = 1;
	while (!ss.eof()) {
		//check if it is valid to put stringstream object into float variable. Also check for every second index - if found multiply with with negative 1 to mirror about y axis.
		if (ss >> found) {
			if ((i % 2) == 0) {
				found = (-1) * found; //mirror the network about the x-axis. This means changing the sign of the y coordinate. 
				Shapecoordinates.push_back(found*100); //Since the default unreal engine unit is cm and the default SUMO unit is m, we perform the conversion here.
				
				i += 1;
			}
			else {
				Shapecoordinates.push_back(found*100);
				i += 1;
			}	
		}
	}
}

void UfileParser::resetFlagsAndTempMembers() {
	isElementNode = false;
	//isTrafficNode = false;
	isPriorityNode = false;
	tempNodeID = "";
	nodeXCoordinate = nullptr;
	nodeYCoordinate = nullptr;
	Shapecoordinates.clear();
	xCoordinateIsSet = false;
	yCoordinateIsSet = false;
	shapeIsSet = false;

	isElementEdge = false;
	isInternalEdge = false;
	tempEdgeID = "";
	fromNode = "";
	toNode = "";
	laneLength = "";
	fromNodeSet = false;
	toNodeSet = false;
	lengthIsSet = false;
}

void UfileParser::InitializeInternalEdgeAttributes(const TCHAR* AttributeName, const TCHAR* AttributeValue) {
	if (FString(AttributeName).Equals(TEXT("id"))) {
		tempEdgeID = FString(AttributeValue);
		return;
	}
	else if (FString(AttributeName).Equals(TEXT("shape"))) {
		ShapeProcessing(AttributeValue);
		shapeIsSet = true;
	}
}

void UfileParser::InitializeEdgeAttributes(const TCHAR* AttributeName, const TCHAR* AttributeValue) {
	if (FString(AttributeName).Equals(TEXT("id"))) {
		tempEdgeID = FString(AttributeValue);
		return;
	}

	else if (FString(AttributeName).Equals(TEXT("from"))) {
		fromNode = FString(AttributeValue);
		fromNodeSet = true;
		return;
	}

	else if (FString(AttributeName).Equals(TEXT("to"))) {
		toNode = FString(AttributeValue);
		toNodeSet = true;
		return;
	}

	else if (FString(AttributeName).Equals(TEXT("length"))) {
		laneLength = FString(AttributeValue);
		lengthIsSet = true;
		return;
	}

	else if (FString(AttributeName).Equals(TEXT("shape"))) {
		if (isElementLane == true) {
			ShapeProcessing(AttributeValue);
			shapeIsSet = true;
		}
		return;
	}

	else if (FString(AttributeName).Equals(TEXT("width"))) {
		laneWidth = FCString::Atof(AttributeValue);
		laneWidthIsSet = true;
	}

	else if (FString(AttributeName).Equals(TEXT("allow"))) {
		isSidewalk = true;
		return;
	}

	else return;
}

//processing the shape coordinates of the regular edge to make a spline. Assumption - vector parameter has 4 elements. 
void UfileParser::MakeSpline(std::vector<float>& shapeCoordinates, FVector& centroid) {
	TArray<FSplinePoint> SplinePoint;
	SplinePoint.Add(FSplinePoint(0.0, FVector((shapeCoordinates[0] - centroid.X), (shapeCoordinates[1] - centroid.Y), 0.2f)));
	SplinePoint.Add(FSplinePoint(1.0, FVector((shapeCoordinates[2] - centroid.X), (shapeCoordinates[3] - centroid.Y), 0.2f)));
}

void UfileParser::MakeSpline() {
	TArray<FSplinePoint> SplinePoint;
	FVector SplineCentroid;
	float sumX = 0;
	float sumY = 0;
	for (int i = 0; i < (Shapecoordinates.size() - 1); i++) {
		if (i % 2 == 0) sumX += Shapecoordinates[i];
		else sumY += Shapecoordinates[i];
	}
	SplineCentroid.X = sumX / (Shapecoordinates.size() / 2);
	SplineCentroid.Y = sumY / (Shapecoordinates.size() / 2);
	SplineCentroid.Z = 0.0f;

	int j = 0;
	float k = 0.0;
	while (j < (Shapecoordinates.size() - 1)) {
		SplinePoint.Add(FSplinePoint(k, FVector((Shapecoordinates[j] - SplineCentroid.X), (Shapecoordinates[j + 1] - SplineCentroid.Y), 0.2f)));
		k += 1.0;
		j += 2;
	}

	FQuat SplineRotation(0.0f, 0.0f, 0.0f, 0.0f);
	FTransform SpawnTransform(SplineRotation, SplineCentroid);
	AWayPoint* WayPointDeferred = Cast<AWayPoint>(UGameplayStatics::BeginDeferredActorSpawnFromClass(World, AWayPoint::StaticClass(), SpawnTransform));

	if (WayPointDeferred != nullptr) {
		WayPointDeferred->SplineComponent->SplineCurves.Position.Points.Empty();
		WayPointDeferred->SplineComponent->SplineCurves.Rotation.Points.Empty();
		WayPointDeferred->SplineComponent->SplineCurves.Scale.Points.Empty(); //Empty the list of default spline points. 
		WayPointDeferred->SplineComponent->AddPoints(SplinePoint);
		UGameplayStatics::FinishSpawningActor(WayPointDeferred, SpawnTransform);
	}

	SimpleSplinePtr SplineComponent = std::make_shared<SimpleSpline>();
	SplineComponent->SplineActor = WayPointDeferred;
	SplineComponent->SplineActor->splineID = tempEdgeID;
	SplineComponent->SplineActor->SpeedLimit = 8;
	SplineComponent->SplineActor->TotalDistance = SplineComponent->SplineActor->SplineComponent->GetSplineLength();
	SplineContainer.SplineMap.Add(WayPointDeferred->splineID, SplineComponent);
	UE_LOG(LogEngine, Warning, TEXT("The added spline is %s"), *(WayPointDeferred->splineID));
}

void UfileParser::InitializetrafficLightAttributes(const TCHAR* AttributeName, const TCHAR* AttributeValue) {
	if (FString(AttributeName).Equals(TEXT("id"))) {
		tempTrafficLightID = FString(AttributeValue);
		return;
	}
}

void UfileParser::InitializeWalkingAreaAttributes(const TCHAR* AttributeName, const TCHAR* AttributeValue) {
	if (FString(AttributeName).Equals(TEXT("id"))) {
		walkingAreaID = FString(AttributeValue);
		return;
	}

	else if ((FString(AttributeName)).Equals(TEXT("shape"))) {
		ShapeProcessing(AttributeValue);
		shapeIsSet = true;
		return;
	}
	else return;
}

void UfileParser::InitializeNodeAttributes(const TCHAR* AttributeName, const TCHAR* AttributeValue) {
	if (FString(AttributeName).Equals(TEXT("id"))) {
		setTempNodeID(AttributeValue);
		return;
	}

	else if ((FString(AttributeValue)).Equals(TEXT("priority"))) {
		isPriorityNode = true;
		return;
	}

	else if ((FString(AttributeValue)).Equals(TEXT("traffic_light")) || FString(AttributeValue).Equals(TEXT("allway_stop"))) {
		isTrafficNode = true;
		/*
		TUniquePtr<FString> tempPointer = MakeUnique<FString>(tempNodeID);//creates a new object which is 'owned' by tempPointer
		trafficControlIDList.Push(MoveTempIfPossible(tempPointer)); 
		use the move constructor to 'move' the ownership of the newly created object to 
		the new unique pointer within trafficControlIDList. As long as the pointer exists,
		the object it is pointing to (the Node ID) will exist. 
		*/
		return;
	}

	//Set temp node positions
	if (((isPriorityNode == true) || (isTrafficNode == true)) && ((FString(AttributeName)).Equals(TEXT("x")))) {
		nodeXCoordinate = AttributeValue;
		xCoordinateIsSet = true;
		return;
	}

	else if (((isPriorityNode == true) || (isTrafficNode == true)) && ((FString(AttributeName)).Equals(TEXT("y")))) {
		nodeYCoordinate = AttributeValue;
		yCoordinateIsSet = true;
		return;
	}

	else if (((isPriorityNode == true) || (isTrafficNode == true)) && ((FString(AttributeName)).Equals(TEXT("shape"))))
	{
		ShapeProcessing(AttributeValue);
		shapeIsSet = true;
		return;
	}

	else if (((isTrafficNode == true)) && (FString(AttributeName).Equals(TEXT("incLanes")))) {
		//code reuse from shape processing function. In future use same code for both purposes. 
		std::string incomingLanes = TCHAR_TO_UTF8(AttributeValue);
		for (std::string::iterator it = incomingLanes.begin(); it != incomingLanes.end(); ++it) {
			if (*it == ',') {
				*it = ' ';
			}
			else continue;			//convert all commas in string stream into space
		}
		std::stringstream ss;
		ss << incomingLanes;
		std::string ind;
		incomingLaneContainer.Empty();
		while (!ss.eof()) {
			ss >> ind;
			FString tempString(ind.c_str());
			UE_LOG(LogEngine, Warning, TEXT("The added incoming lane is %s"), *tempString);
			incomingLaneContainer.Add(tempString);
		}
		return;
	}

	else {
		return;
	}

}

//walking Area parsing is similar to the nodes. TMap storing the walkingArea objects is different. Also walkingArea meshes will be 
//3d at some point. 
void UfileParser::InitializewalkingArea()
{
	//unique_ptr for object creation for extended lifetime
	walkingAreaPtr currentWalkingArea = std::make_unique<walkingArea>();
	currentWalkingArea->walkingAreaShapeCoordinates = Shapecoordinates;
	currentWalkingArea->setWalkingAreaID(*walkingAreaID);

	FQuat RotationEdge(0.0f, 0.0f, 0.0f, 0.0f);
	currentWalkingArea->centroidCalculation();
	FVector origin(currentWalkingArea->centroidX, currentWalkingArea->centroidY, 0.1f);

	walkingAreaPtr movedWalkingAreaPointer = nullptr;

	FTransform SpawnTransform(RotationEdge, origin);
	ARoadMesh* MyDeferredActor = Cast<ARoadMesh>(UGameplayStatics::BeginDeferredActorSpawnFromClass(World, ARoadMesh::StaticClass(), SpawnTransform)); //Downcasting

	if (MyDeferredActor != nullptr)
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
		MyDeferredActor->isSideWalkType = true;
		UGameplayStatics::FinishSpawningActor(MyDeferredActor, SpawnTransform);
		walkingAreaContainer.walkingAreaMap.Add(*(currentWalkingArea->walkingAreaID), std::move(currentWalkingArea));
		/*
		Here we transfer ownership of the object pointed to by 'currentWalkingArea' pointer within the 
		walking area hashmap. As long as the pointer object exists, the object pointed by it will exist. 
		*/
	}
}

SimpleNodePtr UfileParser::InitializeNode()
{
	//unique_ptr for object creation for extended lifetime
	SimpleNodePtr Node = std::make_unique<SimpleNode>();
	Node->SetID(*tempNodeID);
	Node->nodeShapecoordinates = Shapecoordinates;
	Node->SetPosition(nodeXCoordinate, nodeYCoordinate);

	FQuat RotationEdge(0.0f, 0.0f, 0.0f, 0.0f);
	FVector origin(Node->NodePosition.X, Node->NodePosition.Y, 0.0f);

	FTransform SpawnTransform(RotationEdge, origin);
	ARoadMesh* MyDeferredActor = Cast<ARoadMesh>(UGameplayStatics::BeginDeferredActorSpawnFromClass(World, ARoadMesh::StaticClass(), SpawnTransform)); //Downcasting

	if (MyDeferredActor != nullptr) {
		FVector coordinates;
		int i=0;
		while ((i+2) <= Node->nodeShapecoordinates.size()) {		
				coordinates.X = Node->nodeShapecoordinates[i] - Node->NodePosition.X; //node vertex coordinate relative to the node spawn point. 
				coordinates.Y = Node->nodeShapecoordinates[i + 1] - Node->NodePosition.Y;
				coordinates.Z = 0.0f;
				MyDeferredActor->vertices.Add(coordinates);	
				i += 2;
		}
		UGameplayStatics::FinishSpawningActor(MyDeferredActor, SpawnTransform);
		//initialize map with the pointer for extended node lifetime
		NodeContainer.NodeMap.Add(*tempNodeID, std::move(Node));
	}
	return Node;
}

SimpleEdgePtr UfileParser::InitializePedestrianEdge() {
	//unique_ptr for object creation for extended lifetime
	SimpleEdgePtr Edge = std::make_unique<SimpleEdge>();
	Edge->SetID(*tempEdgeID);
	Edge->setFromID(*fromNode);
	Edge->setToID(*toNode);
	Edge->setLaneLength(*laneLength);

	int i = 0;
	std::vector<float> tempvector;
	while ((i + 3) <= (Shapecoordinates.size() - 1)) {
		tempvector.push_back(Shapecoordinates[i]);
		tempvector.push_back(Shapecoordinates[i + 1]);
		tempvector.push_back(Shapecoordinates[i + 2]);
		tempvector.push_back(Shapecoordinates[i + 3]);

		Edge->setShapeCoordinates(tempvector);
		tempvector.clear();

		if (laneWidthIsSet == true) Edge->setSideWalkVertCoordinates(laneWidth*100); //default SUMO lane width
		else Edge->setSideWalkVertCoordinates(320);  //default SUMO lane width is 320cm. Default interstate highway lane width is 470cm (12 feet).

		FVector originCoordinates = Edge->centroid;
		FQuat RotationEdge(0.0f, 0.0f, 0.0f, 0.0f);
		FVector origin(0.0f, 0.0f, 0.0f);
		
		origin.X = originCoordinates.X;
		origin.Y = originCoordinates.Y;
		origin.Z = 0.2f;
		
		FTransform SpawnTransform(RotationEdge, origin);
		ARoadMesh* MyDeferredActor = Cast<ARoadMesh>(UGameplayStatics::BeginDeferredActorSpawnFromClass(World, ARoadMesh::StaticClass(), SpawnTransform)); //Downcasting

		if (MyDeferredActor != nullptr) {
			(MyDeferredActor->vertices) = (Edge->vertexArray);
			MyDeferredActor->isSideWalkType = true;
			UGameplayStatics::FinishSpawningActor(MyDeferredActor, SpawnTransform);
		}

		FVector originCoordinatesCurb1 = Edge->CentroidcurbTop1;
		FQuat RotationEdgeCurb1(0.0f, 0.0f, 0.0f, 0.0f);
		FVector originCurb1(0.0f, 0.0f, 0.0f);

		originCurb1.X = originCoordinatesCurb1.X;
		originCurb1.Y = originCoordinatesCurb1.Y;
		originCurb1.Z = 0.2f;

		FTransform SpawnTransformCurb1(RotationEdgeCurb1, originCurb1);
		ARoadMesh* MyDeferredActor1 = Cast<ARoadMesh>(UGameplayStatics::BeginDeferredActorSpawnFromClass(World, ARoadMesh::StaticClass(), SpawnTransformCurb1)); //Downcasting

		if (MyDeferredActor1 != nullptr){
			MyDeferredActor1->vertices = Edge->curbVerticesTop1;
			MyDeferredActor1->isSideWalkType = true;
			UGameplayStatics::FinishSpawningActor(MyDeferredActor1, SpawnTransformCurb1);
		}

		FVector originCoordinatesCurb2 = Edge->CentroidcurbTop2;
		FQuat RotationEdgeCurb2(0.0f, 0.0f, 0.0f, 0.0f);
		FVector originCurb2(0.0f, 0.0f, 0.0f);

		originCurb2.X = originCoordinatesCurb2.X;
		originCurb2.Y = originCoordinatesCurb2.Y;
		originCurb2.Z = 0.2f;

		FTransform SpawnTransformCurb2(RotationEdgeCurb2, originCurb2);
		ARoadMesh* MyDeferredActor2 = Cast<ARoadMesh>(UGameplayStatics::BeginDeferredActorSpawnFromClass(World, ARoadMesh::StaticClass(), SpawnTransformCurb2)); //Downcasting

		if (MyDeferredActor2 !=nullptr) {
			MyDeferredActor2->vertices = Edge->curbVerticesTop2;
			MyDeferredActor2->isSideWalkType = true;
			UGameplayStatics::FinishSpawningActor(MyDeferredActor2, SpawnTransformCurb2);
		}
		i += 2;
	}
	//initialize map with the pointer for extended node lifetime
	EdgeContainer.EdgeMap.Add(*tempEdgeID, std::move(Edge));	
	return Edge;
}

//function for making an edge actor as well as the edge spline. 
SimpleEdgePtr UfileParser::InitializeEdge(const TCHAR* edgeType) {
	//unique_ptr for object creation for extended lifetime
	SimpleEdgePtr Edge = std::make_unique<SimpleEdge>();
	Edge->SetID(*tempEdgeID);
	Edge->setFromID(*fromNode);
	Edge->setToID(*toNode);
	Edge->setLaneLength(*laneLength);

	int i = 0;
	float j = 0.0;
	std::vector<float> tempvector;
	TArray<FSplinePoint> SplinePoint;
	FVector splineOrigin(0.0f, 0.0f, 0.0f);
	FQuat splineRotation(0.0f, 0.0f, 0.0f, 0.0f);

	while ((i + 3) <= (Shapecoordinates.size() - 1)){  //accounting for smaller edges to make a curved edge.
		float temp[] = { Shapecoordinates[i], Shapecoordinates[i + 1], Shapecoordinates[i + 2], Shapecoordinates[i + 3] };
		tempvector.assign(temp, temp + 4);
		SplinePoint.Empty();
		Edge->setShapeCoordinates(tempvector);
		tempvector.clear();

		if (laneWidthIsSet == true) Edge->setVertexCoordinates(laneWidth);  //default SUMO lane width
		else Edge->setVertexCoordinates(320);  //default SUMO lane width is 320cm. Default interstate highway lane width is 470cm.

		FVector originCoordinates = Edge->centroid;
		FQuat RotationEdge(0.0f, 0.0f, 0.0f, 0.0f);
		FVector origin(0.0f, 0.0f, 0.0f);

		SplinePoint.Add(FSplinePoint(j, FVector((Shapecoordinates[i]-(Edge->centroid.X)), (Shapecoordinates[i + 1]-(Edge->centroid.Y)), 0.2f)));
		SplinePoint.Add(FSplinePoint(j + 1.0, FVector((Shapecoordinates[i + 2]-(Edge->centroid.X)), (Shapecoordinates[i + 3]-(Edge->centroid.Y)), 0.2f)));
		j += 2.0;

		finalSplinePoints.Add(FVector((Shapecoordinates[i + 2] - (Edge->centroid.X)), (Shapecoordinates[i + 3] - (Edge->centroid.Y)), 0.2f)); //change for curved roads. For curved roads check for last iteration first.

		if (FString(edgeType).Equals(TEXT("standard"))) {
			origin.X = originCoordinates.X;
			origin.Y = originCoordinates.Y;
			origin.Z = originCoordinates.Z;
		}
		else if (FString(edgeType).Equals(TEXT("crossing"))) {
			origin.X = originCoordinates.X;
			origin.Y = originCoordinates.Y;
			origin.Z = 0.0f;
		}
		else if (FString(edgeType).Equals(TEXT("sidewalk"))) {
			origin.X = originCoordinates.X;
			origin.Y = originCoordinates.Y;
			origin.Z = 0.0f;
		}

		splineOrigin = origin; //might break for curved edges.
		splineRotation = RotationEdge;
		FTransform SpawnTransform(RotationEdge, origin);
		ARoadMesh* MyDeferredActor = Cast<ARoadMesh>(UGameplayStatics::BeginDeferredActorSpawnFromClass(World, ARoadMesh::StaticClass(), SpawnTransform)); //Downcasting
		if (MyDeferredActor) {
			MyDeferredActor->vertices = Edge->vertexArray;
			MyDeferredActor->roadLength = Edge->LaneLength;
			UGameplayStatics::FinishSpawningActor(MyDeferredActor, SpawnTransform);
			//MyDeferredActor->FinishSpawning(SpawnLocAndRotation);
		}
		i+=2;
	}

	FTransform SpawnTransform(splineRotation, splineOrigin);
	AWayPoint* WayPointDeferred = Cast<AWayPoint>(UGameplayStatics::BeginDeferredActorSpawnFromClass(World, AWayPoint::StaticClass(), SpawnTransform));
	if (WayPointDeferred) {
		WayPointDeferred->SplineComponent->SplineCurves.Position.Points.Empty();
		WayPointDeferred->SplineComponent->SplineCurves.Rotation.Points.Empty();
		WayPointDeferred->SplineComponent->SplineCurves.Scale.Points.Empty();
		WayPointDeferred->SplineComponent->AddPoints(SplinePoint);
		UGameplayStatics::FinishSpawningActor(WayPointDeferred, SpawnTransform);
	}
	SimpleSplinePtr Spline = std::make_shared<SimpleSpline>();
	Spline->SplineActor = WayPointDeferred;
	Spline->SplineActor->splineID = tempEdgeID;
	Spline->SplineActor->SpeedLimit = 20;
	Spline->SplineActor->TotalDistance = Spline->SplineActor->SplineComponent->GetSplineLength();
	SplineContainer.SplineMap.Add(WayPointDeferred->splineID, Spline);
	UE_LOG(LogEngine, Warning, TEXT("The added spline is %s"), *(WayPointDeferred->splineID));

	//Add Edge object to the hashmap.
	EdgeContainer.EdgeMap.Add(*tempEdgeID, std::move(Edge));
	return Edge;
}


void UfileParser::InitializeTrafficControl(const TCHAR* controlType)//spawn two traffic lights per walking area - At the first and fourth x,y coordinate.
{
	walkingArea* currentWalkingAreaObject; 
	FString currentControlNodeID = FString(TEXT(":0_0_"));
	/*
	For stop sign from IntGen --> Netgenerate, we only check for the walking areas within one junction.
	This is to prevent turn lane's junction walking areas to be considered when trying to place the stop sign.
	*/
	FVector trafficControl1Location;
	FQuat trafficControlRotation;
	FVector trafficLightScale(1.0f, 1.0f, 1.0f);
	FVector stopSignScale(50.0f, 50.0f, 50.0f);
	for (const TPair<const TCHAR*, walkingAreaPtr>& pair : walkingAreaContainer.walkingAreaMap)// Find the corresponding walking area for a traffic light for a particular junction.
	{
		FString currentKey = FString(pair.Key); //ID of the walking area.
		/*
		if ((currentKey.Contains(currentControlNodeID)) && (FString(controlType).Equals(TEXT("trafficLight"))))
		{
			currentWalkingAreaObject = pair.Value.get();
			currentWalkingAreaObject->trafficControlLocationCalculator();
			trafficControl1Location = currentWalkingAreaObject->trafficControlLocation;
			trafficControlRotation = currentWalkingAreaObject->trafficLight1Orientation;
			FTransform SpawnTransform(trafficControlRotation, trafficControl1Location, trafficLightScale);
			AtrafficLightMesh* MyDeferredTrafficLight = Cast<AtrafficLightMesh>(UGameplayStatics::BeginDeferredActorSpawnFromClass(World, AtrafficLightMesh::StaticClass(), SpawnTransform)); //Downcasting
			UGameplayStatics::FinishSpawningActor(MyDeferredTrafficLight, SpawnTransform);
		}
		*/
		if ((currentKey.Contains(currentControlNodeID)) && (FString(controlType).Equals(TEXT("stopSign"))))
		{
			currentWalkingAreaObject = pair.Value.get();
			trafficControl1Location = currentWalkingAreaObject->trafficControlLocationCalculator();
			trafficControlRotation = currentWalkingAreaObject->stopSignRotationCalculator();
			FTransform SpawnTransform(trafficControlRotation, trafficControl1Location, stopSignScale);
			AStopSignMesh* MyDeferredStopSign = Cast<AStopSignMesh>(UGameplayStatics::BeginDeferredActorSpawnFromClass(World, AStopSignMesh::StaticClass(), SpawnTransform)); //Downcasting
			UGameplayStatics::FinishSpawningActor(MyDeferredStopSign, SpawnTransform); //deferred actor spawning because it gives us the option to change scale of actor when needed. 
			StopSignContainer.StopSignMap.Add(*currentKey, MyDeferredStopSign);
		}
	}	
}
void UfileParser::InitializeSplineAttributes(const TCHAR* AttributeName, const TCHAR* AttributeValue) {
	if (FString(AttributeName).Equals(TEXT("from"))) fromID = FString(AttributeValue);
	else if (FString(AttributeName).Equals(TEXT("to"))) toID = FString(AttributeValue);
	else if (FString(AttributeName).Equals(TEXT("fromLane"))) {
		fromID = fromID + "_" + FString(AttributeValue);
		UE_LOG(LogEngine, Warning, TEXT("The final from Id is %s"), *fromID);
	}
	else if (FString(AttributeName).Equals(TEXT("toLane"))) toID = toID + "_" + FString(AttributeValue);
	else if (FString(AttributeName).Equals(TEXT("via"))) {
		viaID = FString(AttributeValue);
		viaIsSet = true;
	}
	else if (FString(AttributeName).Equals(TEXT("dir"))) {
		if (FString(AttributeValue).Equals(TEXT("s"))) turnType = "straight";
		else if (FString(AttributeValue).Equals(TEXT("t"))) turnType = "uturn";
		else if (FString(AttributeValue).Equals(TEXT("l"))) turnType = "left";
		else if (FString(AttributeValue).Equals(TEXT("r"))) turnType = "right";
	}
}

void UfileParser::LinkTrafficControlToSplines() {
	for (int g = 0; g < incomingLaneContainer.Num(); g++) {
		UE_LOG(LogEngine, Warning, TEXT("-=-=-=-=-=-incoming lane set is %s-=-=-=-=-=-=-="), *incomingLaneContainer[g]);
		if (incomingLaneContainer[g].Contains(TEXT("w"))) {}
		else {
			UE_LOG(LogEngine, Warning, TEXT("-=-=-=-=-=-Current incoming lane is %s-=-=-=-=-=-=-="), *incomingLaneContainer[g]);
			if (SplineContainer.SplineMap.Contains(incomingLaneContainer[g])) SplineContainer.SplineMap[incomingLaneContainer[g]]->SplineActor->isStopSignConnected = true; //Many incoming lanes in the set for which splines do not exist. 	
		}
	}
}

bool UfileParser::loadxml() {
	FText outError;
	int32 outErrorNum;
	FString Text = "";
	bool success = FFastXml::ParseXmlFile((IFastXmlCallback*)(this), selectedXMLFile.GetCharArray().GetData(), (TCHAR*)*Text, nullptr, false, false, outError, outErrorNum);
	return success;
} 

bool UfileParser::ProcessElement(const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) {
	if ((FString(ElementName)).Equals(TEXT("junction"))) {
		isElementNode = true;
		isElementEdge = false;
	}
	else if ((FString(ElementName)).Equals(TEXT("edge"))) {
		isElementEdge = true;
		isElementNode = false;
	}
	else if ((FString(ElementName)).Equals(TEXT("lane"))) isElementLane = true;
	else if ((FString(ElementName)).Equals(TEXT("tlLogic"))) isElementtrafficLight = true;
	else if ((FString(ElementName)).Equals(TEXT("connection"))) isConnection = true;
	return true;
}

bool UfileParser::ProcessAttribute(const TCHAR* AttributeName, const TCHAR* AttributeValue) {
	//Checking if all the required attributes are populated for the required mesh to be spawned.
	//Attributes are only saved when 

	if (isElementNode == true) InitializeNodeAttributes(AttributeName, AttributeValue);
	else if ((isElementEdge == true) || (isElementLane == true))
	{
		if (FString(AttributeValue).Equals(TEXT("internal"))) {
			isInternalEdge = true;
			return true;
		}
		if (isInternalEdge == true) {
			InitializeInternalEdgeAttributes(AttributeName, AttributeValue);
			if (shapeIsSet == true)
			{
				MakeSpline();
				//shapeIsSet = false;
				//isInternalEdge = false;
			}
		}
		else InitializeEdgeAttributes(AttributeName, AttributeValue);
	}

	if (FString(AttributeValue).Equals(TEXT("walkingarea"))) {
		isWalkingArea = true;
		return true;
	}
	else if (isWalkingArea == true) InitializeWalkingAreaAttributes(AttributeName, AttributeValue);

	if (FString(AttributeValue).Equals(TEXT("crossing"))) {
		isCrossing = true;
		return true;
	}

	else if (isCrossing == true) InitializeEdgeAttributes(AttributeName, AttributeValue);
	if (isElementtrafficLight == true) InitializetrafficLightAttributes(AttributeName, AttributeValue);
	if (isConnection == true) InitializeSplineAttributes(AttributeName, AttributeValue);
	return true;
}

bool UfileParser::ProcessClose(const TCHAR* Element) {
	if ((isElementNode == true) && (shapeIsSet == true) && (xCoordinateIsSet == true) && (yCoordinateIsSet == true)) InitializeNode();

	else if ((fromNodeSet == true) && (toNodeSet == true) && (lengthIsSet == true) && (shapeIsSet == true)){
		if (isSidewalk == true) InitializePedestrianEdge();
		else InitializeEdge(TEXT("standard"));
	}
 	else if ((isCrossing == true) && (shapeIsSet == true)) InitializeEdge(TEXT("crossing"));

	if ((FString(Element)).Equals(TEXT("lane"))) {
		if (isWalkingArea == false) {
			Shapecoordinates.clear();
			shapeIsSet = false;
			lengthIsSet = false;
			isElementLane = false;
			laneWidthIsSet = false;
			isCrossing = false;
			isSidewalk = false;
		}
		else {
			if (shapeIsSet) {
				InitializewalkingArea();
				doesWalkingAreaExist = true;
				Shapecoordinates.clear();
				shapeIsSet = false;
				isWalkingArea = false;
			}
		}
	}
	else
	{
		resetFlagsAndTempMembers();
	}

	if (isConnection == true) {
		if (fromID.Contains(TEXT("w")) || toID.Contains(TEXT("w"))) {} //avoid walking area related splines.  
		else {
			if (viaIsSet == true) SplineContainer.SplineMap[fromID]->SplineActor->ConnectedSpline.Add((SplineContainer.SplineMap[viaID])->SplineActor);
			else SplineContainer.SplineMap[fromID]->SplineActor->ConnectedSpline.Add((SplineContainer.SplineMap[toID])->SplineActor);
		}
		viaIsSet = false;
		isConnection = false;
		fromID.Reset();
		toID.Reset();
		viaID.Reset();
		turnType.Reset();
	}

	if (isTrafficNode == true)
	{
		InitializeTrafficControl(TEXT("stopSign"));
		isElementtrafficLight = false;
		tempTrafficLightID = "";
		isTrafficNode = false;
	}

	if (FString(Element).Equals(TEXT("net"))) {
		LinkTrafficControlToSplines();
		incomingLaneContainer.Empty();
	}
	return true;
}

bool UfileParser::ProcessComment(const TCHAR* Comment)
{
	//UE_LOG(LogEngine, Warning, TEXT("ProcessComment Comment: %s"), Comment);
	return true;
}









