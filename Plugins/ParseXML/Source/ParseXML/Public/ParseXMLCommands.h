// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "ParseXMLStyle.h"

class FParseXMLCommands : public TCommands<FParseXMLCommands>
{
public:

	FParseXMLCommands()
		: TCommands<FParseXMLCommands>(TEXT("ParseXML"), NSLOCTEXT("Contexts", "ParseXML", "ParseXML Plugin"), NAME_None, FParseXMLStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
