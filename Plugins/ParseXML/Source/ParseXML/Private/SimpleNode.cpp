#pragma once
#include "SimpleNode.h"
#include "earcut.h"
//#include "SimpleEdge.h"

SimpleNode::SimpleNode()
{
	
}

SimpleNode::~SimpleNode()
{

}

void SimpleNode::SetID(const TCHAR* tempID)
{
	ID = FString(tempID);
	UE_LOG(LogEngine, Warning, TEXT("New node ID is %s"), tempID);
}

void SimpleNode::SetPosition(const TCHAR* xCoordinate, const TCHAR* yCoordinate)
{
	UE_LOG(LogEngine, Warning, TEXT("New node coordinates are %s %s"), xCoordinate, yCoordinate);
	NodePosition.X = FCString::Atof(xCoordinate);
	NodePosition.Y = FCString::Atof(yCoordinate);
}




