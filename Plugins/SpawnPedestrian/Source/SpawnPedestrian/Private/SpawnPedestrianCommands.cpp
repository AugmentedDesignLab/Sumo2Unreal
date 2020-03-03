// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SpawnPedestrianCommands.h"

#define LOCTEXT_NAMESPACE "FSpawnPedestrianModule"

void FSpawnPedestrianCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "SpawnPedestrian", "Execute SpawnPedestrian action", EUserInterfaceActionType::Button,
	           FInputGesture());
}

#undef LOCTEXT_NAMESPACE
