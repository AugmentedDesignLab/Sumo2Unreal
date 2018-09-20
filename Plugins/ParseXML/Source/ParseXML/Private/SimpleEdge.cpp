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

//FString SimpleEdge::getMyShape() {
//
//}

//tester constructor
SimpleEdge::SimpleEdge(FString id, FString fromNode, FString toNode, double length) {
	setId(id);
	setFrom(fromNode);
	setTo(toNode);
	setLaneLength(length);

}
