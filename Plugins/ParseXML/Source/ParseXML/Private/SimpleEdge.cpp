#include "SimpleEdge.h"
#include "Engine.h"



SimpleEdge::SimpleEdge() {

}

void SimpleEdge::setId(FString id) {
	myID = id;
}

void SimpleEdge::setFrom(FString fromNode) {
	myFromID = fromNode;
}

void SimpleEdge::setTo(FString toNode) {
	myToID = toNode;
}

void SimpleEdge::setLaneLength(double length) {
	myLaneLength = length;
}

void SimpleEdge::setLaneWidth(double width) {
	myLaneWidth = width;
}

void SimpleEdge::setFirstShape(std::pair<double, double> shape) {
	firstShape = shape;
}

void SimpleEdge::setSecondShape(std::pair<double, double> shape) {
	secondShape = shape;
}





FString SimpleEdge::getID() {
	return myID;
}

FString SimpleEdge::getFromID() {
	return myFromID;
}

FString SimpleEdge::getToID() {
	return myToID;
}

double SimpleEdge::getMyLaneLength() {
	return myLaneLength;
}

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
