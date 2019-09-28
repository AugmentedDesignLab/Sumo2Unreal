#include "simpleSidewalk.h"
#include "Engine.h"

simpleSidewalk::simpleSidewalk() {

}

simpleSidewalk::~simpleSidewalk() {

}

void simpleSidewalk::SetID(const TCHAR* id) {
	EdgeID = FString(id);
}

void simpleSidewalk::setShapeCoordinates(const std::vector<float>& inputShapeVector)
{
	edgeShapeCoordinates = inputShapeVector;
}

void simpleSidewalk::setFromID(const TCHAR* fromIDParsed)
{
	fromID = FString(fromIDParsed);
}

void simpleSidewalk::setToID(const TCHAR* toIDParsed)
{
	toID = FString(toIDParsed);
}

FString simpleSidewalk::getID()
{
	return EdgeID;
}

FString simpleSidewalk::getFromID()
{
	return fromNodeID;
}

FString simpleSidewalk::getToID()
{
	return toNodeID;
}

void simpleSidewalk::setLaneLength(const TCHAR* laneLengthParameter)
{
	LaneLength = FCString::Atof(laneLengthParameter);
}

float simpleSidewalk::getLaneLength()
{
	return LaneLength;
}

void simpleSidewalk::setVertexCoordinates(float paralaneWidth)
{
	laneWidth = paralaneWidth;
	FVector Ax0;
	FVector Ax1;

	FVector Bx0;
	FVector Bx1;

	float intermediateTheta = ((std::abs(edgeShapeCoordinates[3] - edgeShapeCoordinates[1])) / std::sqrt((std::pow((edgeShapeCoordinates[3] - edgeShapeCoordinates[1]), 2)) + (std::pow((edgeShapeCoordinates[2] - edgeShapeCoordinates[0]), 2))));

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

	float xOffset = ((laneWidth / 2) * (std::cos((pi_value / 2) - theta)));
	UE_LOG(LogEngine, Warning, TEXT("The value of xOffset is %f"), xOffset);

	float yOffset = ((laneWidth / 2) * (std::sin((pi_value / 2) - theta)));
	UE_LOG(LogEngine, Warning, TEXT("The value of yOffset is %f"), yOffset);

	if (((edgeShapeCoordinates[3] > edgeShapeCoordinates[1]) && (edgeShapeCoordinates[2] > edgeShapeCoordinates[0])) || ((edgeShapeCoordinates[3] < edgeShapeCoordinates[1]) && (edgeShapeCoordinates[2] < edgeShapeCoordinates[0])))
	{	//Case - both x and y of one shape coordinate is greater than the other
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
	}
	else
	{   //either x or y of one vertex is greater but not both
		Ax0.X = edgeShapeCoordinates[0] + xOffset;
		Ax0.Y = edgeShapeCoordinates[1] + yOffset;
		Ax0.Z = 0.0f;
		UE_LOG(LogEngine, Warning, TEXT("Vertex 1: (%f,%f)"), Ax0.X, Ax0.Y);
		vertexArray.Add(Ax0);

		Ax1.X = edgeShapeCoordinates[0] - xOffset;
		Ax1.Y = edgeShapeCoordinates[1] - yOffset;
		Ax1.Z = 0.0f;
		UE_LOG(LogEngine, Warning, TEXT("Vertex 2: (%f,%f)"), Ax1.X, Ax1.Y);
		vertexArray.Add(Ax1);


		Bx0.X = edgeShapeCoordinates[2] + xOffset;
		Bx0.Y = edgeShapeCoordinates[3] + yOffset;
		Bx0.Z = 0.0f;
		UE_LOG(LogEngine, Warning, TEXT("Vertex 3: (%f,%f)"), Bx0.X, Bx0.Y);
		vertexArray.Add(Bx0);


		Bx1.X = edgeShapeCoordinates[2] - xOffset;
		Bx1.Y = edgeShapeCoordinates[3] - yOffset;
		Bx1.Z = 0.0f;
		UE_LOG(LogEngine, Warning, TEXT("Vertex 4: (%f,%f)"), Bx1.X, Bx1.Y);
		vertexArray.Add(Bx1);
	}

	centroid.X = 0.0f;
	centroid.Y = 0.0f;
	centroid.Z = 0.0f;

	for (int i = 0; i < vertexArray.Num(); i++)
	{
		centroid += vertexArray[i];
	}

	centroid.X /= vertexArray.Num();	//Get the centroid vector (average of all 4 vertices)
	centroid.Y /= vertexArray.Num();
	UE_LOG(LogEngine, Warning, TEXT("The centroid vector is (%f, %f, %f)"), centroid.X, centroid.Y, centroid.Z);

	vertexArray.Empty();
	UE_LOG(LogEngine, Warning, TEXT("Vertex Array emptied"));

	Ax0.X = Ax0.X - (centroid.X);  //Update the vertex coordinates relative to centroid
	Ax0.Y = Ax0.Y - (centroid.Y);
	vertexArray.Add(Ax0);

	Ax1.X = Ax1.X - (centroid.X);
	Ax1.Y = Ax1.Y - (centroid.Y);
	vertexArray.Add(Ax1);

	Bx0.X = Bx0.X - (centroid.X);
	Bx0.Y = Bx0.Y - (centroid.Y);


	Bx1.X = Bx1.X - (centroid.X);
	Bx1.Y = Bx1.Y - (centroid.Y);

	vertexArray.Add(Bx1);
	vertexArray.Add(Bx0);

}