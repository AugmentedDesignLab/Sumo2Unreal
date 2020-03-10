// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ParseXML.h"
#include "ParseXMLStyle.h"
#include "ParseXMLCommands.h"
#include "Misc/MessageDialog.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Developer/DesktopPlatform/Public/DesktopPlatformModule.h"
#include "Editor/MainFrame/Public/Interfaces/IMainFrameModule.h"
#include "fileParser.h"

#include "LevelEditor.h"

static const FName ParseXMLTabName("Sumo2Unreal");

#define LOCTEXT_NAMESPACE "FParseXMLModule"

void FParseXMLModule::StartupModule()
{
	
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FParseXMLStyle::Initialize();
	FParseXMLStyle::ReloadTextures();

	FParseXMLCommands::Register();
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FParseXMLCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FParseXMLModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FParseXMLModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FParseXMLModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
}

void FParseXMLModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FParseXMLStyle::Shutdown();

	FParseXMLCommands::Unregister();
}

void FParseXMLModule::PluginButtonClicked()
{

	// Put your "OnButtonClicked" stuff here

	const FString& windowTitle = "Browse XML Files";
	const FString& defaultFilePath = "C:/Users";
	const FString& defaultFileName = "SumoToUnreal.cpp";
	const FString& defaultFileType = "*.jpg";

	TArray <FString> originalOutFileNames = {};
	TArray <FString>& OutFilenames = originalOutFileNames;

	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();

	const void* ParentWindowWindowHandle = nullptr;
	IMainFrameModule& MainFrameModule = FModuleManager::LoadModuleChecked<IMainFrameModule>(TEXT("MainFrame"));
	const TSharedPtr<SWindow>& MainFrameParentWindow = MainFrameModule.GetParentWindow();
	if (MainFrameParentWindow.IsValid() && MainFrameParentWindow->GetNativeWindow().IsValid())
	{
		ParentWindowWindowHandle = MainFrameParentWindow->GetNativeWindow()->GetOSWindowHandle();
		if (DesktopPlatform->OpenFileDialog(ParentWindowWindowHandle, windowTitle, defaultFilePath, defaultFileName,
			defaultFileType, 0x00, OutFilenames))
		{
			FString selectedFile = FString(OutFilenames[0]);
			UfileParser fileParser(*selectedFile); //Selected File from the file dialog

			//Uncomment these lines if you do not want any debug UE_LOG statements
			//GEngine->Exec(nullptr, TEXT("Log LogTemp off")); //comment (1/2) to see log messages
			//GEngine->Exec(nullptr, TEXT("Log LogEngine off")); //comment (2/2) to see log messages

			fileParser.loadxml();
			UE_LOG(LogTemp, Warning, TEXT("Xml file parsed!"));
		}
		
	}
}

void FParseXMLModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FParseXMLCommands::Get().PluginAction);
}

void FParseXMLModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FParseXMLCommands::Get().PluginAction);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FParseXMLModule, ParseXML)