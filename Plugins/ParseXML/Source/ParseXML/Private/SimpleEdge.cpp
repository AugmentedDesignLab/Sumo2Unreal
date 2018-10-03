#include "SimpleEdge.h"
#include "Engine.h"

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


FString SimpleEdge::getID() {
	return EdgeID;
}

FString SimpleEdge::getFromID() {
	return fromNodeID;
}

FString SimpleEdge::getToID() {
	return toNodeID;
}

void SimpleEdge::setLaneLength(const TCHAR* laneLengthParameter)
{
	LaneLength = FCString::Atof(laneLengthParameter);
}

float SimpleEdge::getLaneLength() {
	return LaneLength;
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
