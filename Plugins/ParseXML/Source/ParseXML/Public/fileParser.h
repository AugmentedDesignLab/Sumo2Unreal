#pragma once
#include "Runtime/XmlParser/Public/FastXml.h"
#include "Runtime/XmlParser/Public/XmlParser.h"


class UfileParser : public IFastXmlCallback
{
public:
	UfileParser();
	~UfileParser();

	//IFastXMLCallback
	bool ProcessXmlDeclaration(const TCHAR* ElementData, int32 XmlFileLineNumber);
	bool ProcessElement(const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber);
	bool ProcessAttribute(const TCHAR* AttributeName, const TCHAR* AttributeValue);
	bool ProcessClose(const TCHAR* Element);
	bool ProcessComment(const TCHAR* Comment);
	bool loadxml();
};
