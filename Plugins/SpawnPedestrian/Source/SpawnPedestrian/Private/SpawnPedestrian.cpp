// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SpawnPedestrian.h"
#include "SpawnPedestrianStyle.h"
#include "SpawnPedestrianCommands.h"
#include "Misc/MessageDialog.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

#include "LevelEditor.h"
#include "SpawnManager.h"

static const FName SpawnPedestrianTabName("SpawnPedestrian");

#define LOCTEXT_NAMESPACE "FSpawnPedestrianModule"

void FSpawnPedestrianModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FSpawnPedestrianStyle::Initialize();
	FSpawnPedestrianStyle::ReloadTextures();

	FSpawnPedestrianCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FSpawnPedestrianCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FSpawnPedestrianModule::PluginButtonClicked),
		FCanExecuteAction());

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands,
		                               FMenuExtensionDelegate::CreateRaw(
			                               this, &FSpawnPedestrianModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}

	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands,
		                                     FToolBarExtensionDelegate::CreateRaw(
			                                     this, &FSpawnPedestrianModule::AddToolbarExtension));

		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
}

void FSpawnPedestrianModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FSpawnPedestrianStyle::Shutdown();

	FSpawnPedestrianCommands::Unregister();
}

void FSpawnPedestrianModule::PluginButtonClicked()
{
	// Main entry point to my Plugin
	FSpawnManager::LoadBlueprintAssets();
	FSpawnManager::InitializeNavMesh();
}

void FSpawnPedestrianModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FSpawnPedestrianCommands::Get().PluginAction);
}

void FSpawnPedestrianModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FSpawnPedestrianCommands::Get().PluginAction);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FSpawnPedestrianModule, SpawnPedestrian)
