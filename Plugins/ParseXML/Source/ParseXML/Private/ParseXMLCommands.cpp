// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ParseXMLCommands.h"

#define LOCTEXT_NAMESPACE "FParseXMLModule"

void FParseXMLCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "Sumo2Unreal", "Execute ParseXML action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
