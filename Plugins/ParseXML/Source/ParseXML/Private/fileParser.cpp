#include "fileParser.h"
#include "Runtime/XmlParser/Public/FastXml.h"
#include "Runtime/XmlParser/Public/XmlParser.h"
#include "Engine.h"

UfileParser::UfileParser()
{

}

UfileParser::~UfileParser()
{

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
	UE_LOG(LogEngine, Warning, TEXT("ProcessElement ElementName: %s, ElementValue: %s"), ElementName, ElementData);
	return true;
}

bool UfileParser::ProcessAttribute(const TCHAR* AttributeName, const TCHAR* AttributeValue)
{
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









