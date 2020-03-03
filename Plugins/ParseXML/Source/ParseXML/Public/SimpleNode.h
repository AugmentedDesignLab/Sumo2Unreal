#pragma once
#include "Engine.h"
#include "Platform.h"
#include <vector>

class PARSEXML_API SimpleNode
{
	friend class UfileParser;
public: 
	SimpleNode();
	~SimpleNode();

	//Access Functions
	void SetPosition(const TCHAR*, const TCHAR*);
	void SetID(const TCHAR*);

private:
	FVector NodePosition;
	std::vector<float> nodeShapecoordinates;
	FString ID;
};
