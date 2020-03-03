// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "SpawnPedestrianStyle.h"

class FSpawnPedestrianCommands : public TCommands<FSpawnPedestrianCommands>
{
public:

	FSpawnPedestrianCommands()
		: TCommands<FSpawnPedestrianCommands>(
			TEXT("SpawnPedestrian"), NSLOCTEXT("Contexts", "SpawnPedestrian", "SpawnPedestrian Plugin"), NAME_None,
			FSpawnPedestrianStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> PluginAction;
};
