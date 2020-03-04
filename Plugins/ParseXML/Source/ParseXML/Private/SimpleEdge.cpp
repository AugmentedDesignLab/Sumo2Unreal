#include "SimpleEdge.h"
#include "Engine.h"

const float pi_value = std::acos(-1);
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

void SimpleEdge::centroidAdjustment(const TCHAR* vertexType, FVector Ax0, FVector Ax0_s, FVector Ax1, FVector Ax1_s, FVector Bx0, FVector Bx0_s, FVector Bx1, FVector Bx1_s)
{
	if (FString(vertexType).Equals(TEXT("vertexArray")))
	{
		centroid.X = 0.0f;
		centroid.Y = 0.0f;
		centroid.Z = 0.0f;
		for (int i = 0; i < vertexArray.Num(); i++)
		{
			centroid += vertexArray[i];
		}
		centroid.X /= vertexArray.Num();	//Get the centroid vector (average of all 4 vertices)
		centroid.Y /= vertexArray.Num();
		vertexArray.Empty();
		Ax0_s.X = Ax0_s.X - (centroid.X);  //Update the vertex coordinates relative to centroid
		Ax0_s.Y = Ax0_s.Y - (centroid.Y);
		vertexArray.Add(Ax0_s);
		UE_LOG(LogEngine, Warning, TEXT("===============Vertex: (%f,%f)"), Ax0_s.X, Ax0_s.Y);
		Ax1_s.X = Ax1_s.X - (centroid.X);
		Ax1_s.Y = Ax1_s.Y - (centroid.Y);
		vertexArray.Add(Ax1_s);
		UE_LOG(LogEngine, Warning, TEXT("===============Vertex: (%f,%f)"), Ax1_s.X, Ax1_s.Y);
		Bx0_s.X = Bx0_s.X - (centroid.X);
		Bx0_s.Y = Bx0_s.Y - (centroid.Y);
		Bx1_s.X = Bx1_s.X - (centroid.X);
		Bx1_s.Y = Bx1_s.Y - (centroid.Y);
		vertexArray.Add(Bx1_s);
		UE_LOG(LogEngine, Warning, TEXT("===============Vertex: (%f,%f)"), Bx1_s.X, Bx1_s.Y);
		vertexArray.Add(Bx0_s);
		UE_LOG(LogEngine, Warning, TEXT("===============Vertex: (%f,%f)"), Bx0_s.X, Bx0_s.Y);
	}
	else if (FString(vertexType).Equals(TEXT("curbVerticesTop1")))
	{
		CentroidcurbTop1.X = 0.0f;
		CentroidcurbTop1.Y = 0.0f;
		CentroidcurbTop1.Z = 0.0f;
		for (int i = 0; i < curbVerticesTop1.Num(); i++)
		{
			CentroidcurbTop1 += curbVerticesTop1[i];
		}
		CentroidcurbTop1.X /= curbVerticesTop1.Num();	//Get the CentroidcurbTop1 vector (average of all 4 vertices)
		CentroidcurbTop1.Y /= curbVerticesTop1.Num();
		curbVerticesTop1.Empty();
		Ax0_s.X = Ax0_s.X - (CentroidcurbTop1.X);  //Update the vertex coordinates relative to CentroidcurbTop1
		Ax0_s.Y = Ax0_s.Y - (CentroidcurbTop1.Y);
		curbVerticesTop1.Add(Ax0_s);
		UE_LOG(LogEngine, Warning, TEXT("=====curbtop1===============Vertex: (%f,%f)"), Ax0_s.X, Ax0_s.Y);
		Ax0.X = Ax0.X - (CentroidcurbTop1.X);
		Ax0.Y = Ax0.Y - (CentroidcurbTop1.Y);
		curbVerticesTop1.Add(Ax0);
		UE_LOG(LogEngine, Warning, TEXT("=====curbtop1===============Vertex: (%f,%f)"), Ax0.X, Ax0.Y);
		Bx0_s.X = Bx0_s.X - (CentroidcurbTop1.X);
		Bx0_s.Y = Bx0_s.Y - (CentroidcurbTop1.Y);
		Bx0.X = Bx0.X - (CentroidcurbTop1.X);
		Bx0.Y = Bx0.Y - (CentroidcurbTop1.Y);
		curbVerticesTop1.Add(Bx0);
		UE_LOG(LogEngine, Warning, TEXT("=====curbtop1===============Vertex: (%f,%f)"), Bx0_s.X, Bx0_s.Y);
		curbVerticesTop1.Add(Bx0_s);
		UE_LOG(LogEngine, Warning, TEXT("=====curbtop1===============Vertex: (%f,%f)"), Bx0.X, Bx0.Y);
	}
	else if (FString(vertexType).Equals(TEXT("curbVerticesTop2")))
	{

		CentroidcurbTop2.X = 0.0f;
		CentroidcurbTop2.Y = 0.0f;
		CentroidcurbTop2.Z = 0.0f;
		for (int i = 0; i < curbVerticesTop2.Num(); i++)
		{
			CentroidcurbTop2 += curbVerticesTop2[i];
		}
		CentroidcurbTop2.X /= curbVerticesTop2.Num();	//Get the CentroidcurbTop2 vector (average of all 4 vertices)
		CentroidcurbTop2.Y /= curbVerticesTop2.Num();
		curbVerticesTop2.Empty();
		Ax1_s.X = Ax1_s.X - (CentroidcurbTop2.X);  //Update the vertex coordinates relative to CentroidcurbTop2
		Ax1_s.Y = Ax1_s.Y - (CentroidcurbTop2.Y);
		curbVerticesTop2.Add(Ax1_s);
		Ax1.X = Ax1.X - (CentroidcurbTop2.X);
		Ax1.Y = Ax1.Y - (CentroidcurbTop2.Y);
		curbVerticesTop2.Add(Ax1);
		Bx1_s.X = Bx1_s.X - (CentroidcurbTop2.X);
		Bx1_s.Y = Bx1_s.Y - (CentroidcurbTop2.Y);
		Bx1.X = Bx1.X - (CentroidcurbTop2.X);
		Bx1.Y = Bx1.Y - (CentroidcurbTop2.Y);
		curbVerticesTop2.Add(Bx1);
		curbVerticesTop2.Add(Bx1_s);
	}
}

void SimpleEdge::setSideWalkVertCoordinates(float paralaneWidth)
{
	laneWidth = paralaneWidth;
	FVector Ax0;
	FVector Ax0_s;
	FVector Ax1;
	FVector Ax1_s;

	FVector Bx0;
	FVector Bx0_s;
	FVector Bx1;
	FVector Bx1_s;

	float intermediateTheta = ((std::abs(edgeShapeCoordinates[3] - edgeShapeCoordinates[1])) / std::sqrt((std::pow((edgeShapeCoordinates[3] - edgeShapeCoordinates[1]), 2)) + (std::pow((edgeShapeCoordinates[2] - edgeShapeCoordinates[0]), 2))));

	if (intermediateTheta > 1.0) intermediateTheta = 1.0; // clamp domain to -1 .. 1

	else if (intermediateTheta < -1.0) intermediateTheta = -1.0;

	float theta = std::asin(intermediateTheta);
	float xOffset = ((laneWidth / 2) * (std::cos((pi_value / 2) - theta)));
	float yOffset = ((laneWidth / 2) * (std::sin((pi_value / 2) - theta)));

	if (((edgeShapeCoordinates[3] > edgeShapeCoordinates[1]) && (edgeShapeCoordinates[2] > edgeShapeCoordinates[0])) || ((edgeShapeCoordinates[3] < edgeShapeCoordinates[1]) && (edgeShapeCoordinates[2] < edgeShapeCoordinates[0])))
	{	//Case - both x and y of one shape coordinate is greater than the other
		Ax0.X = edgeShapeCoordinates[0] - xOffset;
		Ax0.Y = edgeShapeCoordinates[1] + yOffset;
		Ax0.Z = 0.0f;
		curbVerticesTop1.Add(Ax0);

		Ax0_s.X = edgeShapeCoordinates[0] - xOffset + (float)(0.25*xOffset);
		Ax0_s.Y = edgeShapeCoordinates[1] + yOffset - (float)(0.25*yOffset);
		Ax0_s.Z = 0.0f;
		vertexArray.Add(Ax0_s);
		curbVerticesTop1.Add(Ax0_s);
		

		Ax1.X = edgeShapeCoordinates[0] + xOffset;
		Ax1.Y = edgeShapeCoordinates[1] - yOffset;
		Ax1.Z = 0.0f;
		curbVerticesTop2.Add(Ax1);

		Ax1_s.X = edgeShapeCoordinates[0] + xOffset - (float)(0.25*xOffset);
		Ax1_s.Y = edgeShapeCoordinates[1] - yOffset + (float)(0.25*yOffset);
		Ax1_s.Z = 0.0f;
		vertexArray.Add(Ax1_s);
		curbVerticesTop2.Add(Ax1_s);


		Bx0.X = edgeShapeCoordinates[2] - xOffset;
		Bx0.Y = edgeShapeCoordinates[3] + yOffset;
		Bx0.Z = 0.0f;
		curbVerticesTop1.Add(Bx0);

		Bx0_s.X = edgeShapeCoordinates[2] - xOffset + (float)(0.25*xOffset);
		Bx0_s.Y = edgeShapeCoordinates[3] + yOffset - (float)(0.25*yOffset);
		Bx0_s.Z = 0.0f;
		vertexArray.Add(Bx0_s);
		curbVerticesTop1.Add(Bx0_s);


		Bx1.X = edgeShapeCoordinates[2] + xOffset;
		Bx1.Y = edgeShapeCoordinates[3] - yOffset;
		Bx1.Z = 0.0f;
		curbVerticesTop2.Add(Bx1);

		Bx1_s.X = edgeShapeCoordinates[2] + xOffset - (float)(0.25*xOffset);
		Bx1_s.Y = edgeShapeCoordinates[3] - yOffset + (float)(0.25*yOffset);
		Bx1_s.Z = 0.0f;
		vertexArray.Add(Bx1_s);
		curbVerticesTop2.Add(Bx1_s);
	}
	else
	{   //either x or y of one vertex is greater but not both
		Ax0.X = edgeShapeCoordinates[0] + xOffset;
		Ax0.Y = edgeShapeCoordinates[1] + yOffset;
		Ax0.Z = 0.0f;
		curbVerticesTop1.Add(Ax0);

		Ax0_s.X = edgeShapeCoordinates[0] + xOffset - (float)(0.25*xOffset);
		Ax0_s.Y = edgeShapeCoordinates[1] + yOffset - (float)(0.25*yOffset);
		Ax0_s.Z = 0.0f;
		vertexArray.Add(Ax0_s);
		curbVerticesTop1.Add(Ax0_s);

		Ax1.X = edgeShapeCoordinates[0] - xOffset;
		Ax1.Y = edgeShapeCoordinates[1] - yOffset;
		Ax1.Z = 0.0f;
		curbVerticesTop2.Add(Ax1);

		Ax1_s.X = edgeShapeCoordinates[0] - xOffset + (float)(0.25*xOffset);
		Ax1_s.Y = edgeShapeCoordinates[1] - yOffset + (float)(0.25*yOffset);
		Ax1_s.Z = 0.0f;
		vertexArray.Add(Ax1_s);
		curbVerticesTop2.Add(Ax1_s);


		Bx0.X = edgeShapeCoordinates[2] + xOffset;
		Bx0.Y = edgeShapeCoordinates[3] + yOffset;
		Bx0.Z = 0.0f;
		curbVerticesTop1.Add(Bx0);

		Bx0_s.X = edgeShapeCoordinates[2] + xOffset - (float)(0.25*xOffset);
		Bx0_s.Y = edgeShapeCoordinates[3] + yOffset - (float)(0.25*yOffset);
		Bx0_s.Z = 0.0f;
		curbVerticesTop1.Add(Bx0_s);


		Bx1.X = edgeShapeCoordinates[2] - xOffset;
		Bx1.Y = edgeShapeCoordinates[3] - yOffset;
		Bx1.Z = 0.0f;
		curbVerticesTop2.Add(Bx1);

		Bx1_s.X = edgeShapeCoordinates[2] - xOffset + (float)(0.25*xOffset);
		Bx1_s.Y = edgeShapeCoordinates[3] - yOffset + (float)(0.25*yOffset);
		Bx1_s.Z = 0.0f;
		vertexArray.Add(Bx1_s);
		curbVerticesTop2.Add(Bx1_s);
	}	
	centroidAdjustment(TEXT("vertexArray"), Ax0, Ax0_s, Ax1, Ax1_s, Bx0, Bx0_s, Bx1, Bx1_s);
	centroidAdjustment(TEXT("curbVerticesTop1"), Ax0, Ax0_s, Ax1, Ax1_s, Bx0, Bx0_s, Bx1, Bx1_s);
	centroidAdjustment(TEXT("curbVerticesTop2"), Ax0, Ax0_s, Ax1, Ax1_s, Bx0, Bx0_s, Bx1, Bx1_s);	
}

void SimpleEdge::setVertexCoordinates(float paralaneWidth) 
{
	laneWidth = paralaneWidth;
	FVector Ax0, Ax1, Bx0, Bx1;
	float intermediateTheta = ((std::abs(edgeShapeCoordinates[3] - edgeShapeCoordinates[1])) / std::sqrt((std::pow((edgeShapeCoordinates[3] - edgeShapeCoordinates[1]),2))+(std::pow((edgeShapeCoordinates[2] - edgeShapeCoordinates[0]), 2))));
	
	if (intermediateTheta > 1.0) intermediateTheta = 1.0; // clamp domain to -1 .. 1
	else if (intermediateTheta < -1.0) intermediateTheta = -1.0;

	float theta = std::asin(intermediateTheta);
	float xOffset = ((laneWidth / 2)*(std::cos((pi_value / 2) - theta)));
	float yOffset = ((laneWidth / 2)*(std::sin((pi_value / 2) - theta)));
	
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

	for (int i = 0; i < vertexArray.Num(); i++) {
		centroid += vertexArray[i];
	}

	centroid.X /= vertexArray.Num();	//Get the centroid vector (average of all 4 vertices)
	centroid.Y /= vertexArray.Num();
	UE_LOG(LogEngine, Warning, TEXT("The centroid vector is (%f, %f, %f)"), centroid.X, centroid.Y, centroid.Z);

	vertexArray.Empty();
	UE_LOG(LogEngine, Warning, TEXT("Vertex Array emptied"));

	Ax0.X = Ax0.X - (centroid.X);  //Update the vertex coordinates to be relative to centroid
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

void SimpleEdge::SpawnEdgeMesh()
{
	
}


