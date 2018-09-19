#include "SimpleEdge.h";
#include "Engine.h"


//SimpleEdge::SimpleEdge(FString id, SimpleNode* fromNode, SimpleNode* toNode, double length, FString shape) {
//
//}



void SimpleEdge::setId(FString id) {
	myID = id;
}

//void SimpleEdge::setFrom(SimpleNode* fromNode) {
//	myFrom = fromNode;
//}
//
//void SimpleEdge::setTo(SimpleNode* toNode) {
//	myTo = toNode;
//}

void SimpleEdge::setLaneLength(double length) {
	myLaneLength = length;
}

void SimpleEdge::setLaneWidth(double width) {
	myLaneWidth = width;
}

//tester constructor
SimpleEdge::SimpleEdge(FString id, FString fromNode, FString toNode, double length) {
	setId(id);
	setFrom(fromNode);
	setTo(toNode);
	setLaneLength(length);

}
//tester function
void SimpleEdge::setFrom(FString fromNode) {
	myFromTest = fromNode;
}
//tester function
void SimpleEdge::setTo(FString toNode) {
	myToTest = toNode;
}