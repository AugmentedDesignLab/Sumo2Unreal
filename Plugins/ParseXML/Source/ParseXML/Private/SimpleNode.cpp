#include "SimpleNode.h"


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
	NodePosition.Y = (-1) * NodePosition.Y; //To mirror the network about the X axis.
	NodePosition.X *= 100;
	NodePosition.Y *= 100; //To convert SUMO units (m) from which this is derived to Unreal units (cm). 
}




