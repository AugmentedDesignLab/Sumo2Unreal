#include "SimpleEdge.h"
#include "Engine.h"

const float pi = std::acos(-1);
SimpleEdge::SimpleEdge() {

}

SimpleEdge::~SimpleEdge() {

}

void SimpleEdge::SetID(const TCHAR* id) {
	EdgeID = FString(id);
}

void SimpleEdge::setShapeCoordinates(const std::vector<float>& inputShapeVector)
{
	edgeShapeCoordinates = inputShapeVector;
}

void SimpleEdge::setFromID(const TCHAR* fromIDParsed)
{
	fromID = FString(fromIDParsed);
}

void SimpleEdge::setToID(const TCHAR* toIDParsed)
{
	toID = FString(toIDParsed);
}

/*
void SimpleEdge::setLaneWidth(double width) {
	myLaneWidth = width;
}

void SimpleEdge::setFirstShape(std::pair<double, double> shape) {
	firstShape = shape;
}

void SimpleEdge::setSecondShape(std::pair<double, double> shape) {
	secondShape = shape;
}
*/


FString SimpleEdge::getID() 
{
	return EdgeID;
}

FString SimpleEdge::getFromID() 
{
	return fromNodeID;
}

FString SimpleEdge::getToID() 
{
	return toNodeID;
}

void SimpleEdge::setLaneLength(const TCHAR* laneLengthParameter)
{
	LaneLength = FCString::Atof(laneLengthParameter);
}

float SimpleEdge::getLaneLength() 
{
	return LaneLength;
}

void SimpleEdge::setVertexCoordinates() 
{
	FVector Ax0;
	FVector Ax1;

	FVector Bx0;
	FVector Bx1;

	float intermediateTheta = ((edgeShapeCoordinates[3] - edgeShapeCoordinates[1]) / LaneLength);
	
	if (intermediateTheta > 1.0)
	{
		intermediateTheta = 1.0; // clamp domain to -1 .. 1
	}

	if (intermediateTheta < -1.0)
	{
		intermediateTheta = -1.0;
	}

	float theta = std::asin(intermediateTheta);
	UE_LOG(LogEngine, Warning, TEXT("theta is %f"), theta);

	float xOffset = ((laneWidth / 2)*(std::cos((pi / 2) - theta)));
	UE_LOG(LogEngine, Warning, TEXT("The value of xOffset is %f"), xOffset);

	float yOffset = ((laneWidth / 2)*(std::sin((pi / 2) - theta)));
	UE_LOG(LogEngine, Warning, TEXT("The value of yOffset is %f"), yOffset);

	Ax0.X = edgeShapeCoordinates[0] - xOffset;
	Ax0.Y = edgeShapeCoordinates[1] + yOffset;
	Ax0.Z = 0.0f;
	UE_LOG(LogEngine, Warning, TEXT("Vertex 1: (%f,%f)"), Ax0.X, Ax0.Y);
	vertexArray.Add(Ax0);

	Ax1.X = edgeShapeCoordinates[0] + xOffset;
	Ax1.Y = edgeShapeCoordinates[1] - yOffset;
	Ax1.Z = 0.0f;
	UE_LOG(LogEngine, Warning, TEXT("Vertex 2: (%f,%f)"), Ax1.X, Ax1.Y);
	vertexArray.Add(Ax1);


	Bx0.X = edgeShapeCoordinates[2] - xOffset;
	Bx0.Y = edgeShapeCoordinates[3] + yOffset;
	Bx0.Z = 0.0f;
	UE_LOG(LogEngine, Warning, TEXT("Vertex 3: (%f,%f)"), Bx0.X, Bx0.Y);
	vertexArray.Add(Bx0);


	Bx1.X = edgeShapeCoordinates[2] + xOffset;
	Bx1.Y = edgeShapeCoordinates[3] - yOffset;
	Bx1.Z = 0.0f;
	UE_LOG(LogEngine, Warning, TEXT("Vertex 4: (%f,%f)"), Bx1.X, Bx1.Y);
	vertexArray.Add(Bx1);


	FVector* centroid = new FVector();

	centroid->X = 0.0f;
	centroid->Y = 0.0f;
	centroid->Z = 0.0f;

	for (int i = 0; i < vertexArray.Num(); i++)
	{
		*centroid += vertexArray[i];
	}

	centroid->X /= vertexArray.Num();	//Get the centroid vector (average of all 4 vertices)
	centroid->Y /= vertexArray.Num();
	UE_LOG(LogEngine, Warning, TEXT("The centroid vector is (%f, %f, %f)"), centroid->X, centroid->Y, centroid->Z);

	for (int i = 0; i < vertexArray.Num(); i++)
	{
		FVector dir = vertexArray[i] - *centroid;		//Direction vector A to B. Calculated using (FVector B - FVector A)

		float angle = std::atan2((vertexArray[i].Y - centroid->Y), (vertexArray[i].X - centroid->X)) + pi;		//convert direction vector to heading angle to get it in 0-2pi range
		if (i == 3)
		{
			angle -= 0.00001;  // hack to handle case where final two angles are identical, force ordering to 3 then 2
		}
		float actualVertexIndex = (float)(i + 1); //just for logging purposes
		
		UE_LOG(LogEngine, Warning, TEXT("The atan2 angle for vertex %f is %f"), actualVertexIndex, angle);
		vertexAnglesUnSorted.Add(angle);		//Add vertex angles to a Tarray
	}

	vertexAnglesSorted = vertexAnglesUnSorted; //copy to another array
	vertexAnglesSorted.Sort(); //new array of sorted angles
	delete centroid;

}

void SimpleEdge::SpawnEdgeMesh()
{
	
}

/*
double SimpleEdge::getMyLaneWidth() {
	return myLaneWidth;
}

std::pair<double, double> SimpleEdge::getFirstShape() {
	return firstShape;
}

std::pair<double, double> SimpleEdge::getSecondShape() {
	return secondShape;
}

//tester constructor
SimpleEdge::SimpleEdge(FString id, FString fromNode, FString toNode, double length) {
	setId(id);
	setFrom(fromNode);
	setTo(toNode);
	setLaneLength(length);

}
*/
