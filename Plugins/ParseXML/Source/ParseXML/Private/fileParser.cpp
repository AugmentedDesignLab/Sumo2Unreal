#include "fileParser.h"
#include "Runtime/XmlParser/Public/FastXml.h"
#include "Runtime/XmlParser/Public/XmlParser.h"
#include "Engine.h"
#include "SimpleNode.h"

#include <sstream>
#include <memory>


UfileParser::UfileParser()
{

}

UfileParser::~UfileParser()
{

}

FString UfileParser::getTempNodeID()
{
	return tempNodeID;
}

bool UfileParser::setTempNodeID(const TCHAR* tempTempNodeID)
{
	tempNodeID = FString(tempTempNodeID);
	return (tempNodeID.IsEmpty());

}

void UfileParser::ShapeProcessing(const TCHAR* ShapeString)
{
	std::string CoordinateString = TCHAR_TO_UTF8(ShapeString);
	Shapecoordinates.clear();
	for (std::string::iterator it = CoordinateString.begin(); it != CoordinateString.end(); ++it) 
	{
		if (*it == ',') 
		{
			*it = ' ';
		}
		else continue;			//convert all commas in string stream into space
	}
	
	std::stringstream ss;
	ss << CoordinateString;

	float found;

	while (!ss.eof()) 
	{
		//check if it is valid to put stringstream object into float variable
		if (ss >> found)
		{
			Shapecoordinates.push_back(found);
		}
	}
}

void UfileParser::resetFlagsAndTempMembers()
{
	//isElementNode = false;
	isPriorityNode = false;
	tempNodeID = "";
	nodeXCoordinate = nullptr;
	nodeYCoordinate = nullptr;
	Shapecoordinates.clear();
	xCoordinateIsSet = false;
	yCoordinateIsSet = false;
	shapeIsSet = false;
}

void UfileParser::InitializeNodeAttributes(const TCHAR* AttributeName, const TCHAR* AttributeValue)
{

	if (FString(AttributeName).Equals(TEXT("id")))
	{
		setTempNodeID(AttributeValue);
		return;
	}

	if (((FString(AttributeValue)).Equals(TEXT("priority"))))
	{
		isPriorityNode = true;
		return;
	}

	//Set temp node positions
	if ((isPriorityNode == true) && ((FString(AttributeName)).Equals(TEXT("x"))))
	{
		UE_LOG(LogEngine, Warning, TEXT("Attribute name is %s"), AttributeName);
		UE_LOG(LogEngine, Warning, TEXT("Attribute value is %s"), AttributeValue);
		nodeXCoordinate = AttributeValue;
		xCoordinateIsSet = true;
		return;
	}

	else if ((isPriorityNode == true) && ((FString(AttributeName)).Equals(TEXT("y"))))
	{
		UE_LOG(LogEngine, Warning, TEXT("Attribute name is %s"), AttributeName);
		UE_LOG(LogEngine, Warning, TEXT("Attribute value is %s"), AttributeValue);
		nodeYCoordinate = AttributeValue;
		yCoordinateIsSet = true;
		return;
	}

	else if ((isPriorityNode == true) && ((FString(AttributeName)).Equals(TEXT("shape"))))
	{
		ShapeProcessing(AttributeValue);
		shapeIsSet = true;
		return;
	}

	else
	{
		return;
	}

	UE_LOG(LogEngine, Warning, TEXT("Node Attributes initialized!"));

}

SimpleNodePtr UfileParser::InitializeNode()
{
	//unique_ptr for object creation for extended lifetime
	SimpleNodePtr Node = std::make_unique<SimpleNode>();
	Node->SetID(*tempNodeID);
	Node->nodeShapecoordinates = Shapecoordinates;
	Node->SetPosition(nodeXCoordinate, nodeYCoordinate);

	//initialize map with the pointer for extended lifetime
	NodeContainer.NodeMap.Add(*tempNodeID, Node.get());
	return Node;
}

bool UfileParser::loadxml()
{
	FText outError;
	int32 outErrorNum;
	FString XML = "C:/Users/iparanja/net.net.xml";
	bool success = FFastXml::ParseXmlFile((IFastXmlCallback*)(this), XML.GetCharArray().GetData(), TEXT(""), nullptr, false, false, outError, outErrorNum);
	return success;
}

bool UfileParser::ProcessXmlDeclaration(const TCHAR* ElementData, int32 XmlFileLineNumber)
{
	UE_LOG(LogEngine, Warning, TEXT("ProcessXmlDeclaration ElementData: %s, XmlFileLineNumber: %f"), ElementData, XmlFileLineNumber);
	return true;
}

bool UfileParser::ProcessElement(const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber)
{
	if ((FString(ElementName)).Equals(TEXT("junction")))
	{
		isElementNode = true;
	}
	else if ((FString(ElementName)).Equals(TEXT("edge")))
	{
		isElementEdge = true;
		isElementNode = false;
	}
	else
	{
		isElementNode = false;
	}


	UE_LOG(LogEngine, Warning, TEXT("ProcessElement ElementName: %s, ElementValue: %s"), ElementName, ElementData);
	return true;
}

bool UfileParser::ProcessAttribute(const TCHAR* AttributeName, const TCHAR* AttributeValue)
{
	if (isElementNode == true)
	{
		InitializeNodeAttributes(AttributeName, AttributeValue);
		if ((shapeIsSet == true) && (xCoordinateIsSet == true) && (yCoordinateIsSet == true))
		{
			InitializeNode();
			resetFlagsAndTempMembers();
			UE_LOG(LogEngine, Warning, TEXT("Node object created!"));
		}
		
	}
	UE_LOG(LogEngine, Warning, TEXT("ProcessAttribute AttributeName: %s, AttributeValue: %s"), AttributeName, AttributeValue);

	return true;
}

bool UfileParser::ProcessClose(const TCHAR* Element)
{
	UE_LOG(LogEngine, Warning, TEXT("ProcessClose Element %s"), Element);
	return true;
}

bool UfileParser::ProcessComment(const TCHAR* Comment)
{
	UE_LOG(LogEngine, Warning, TEXT("ProcessComment Comment: %s"), Comment);
	return true;
}









