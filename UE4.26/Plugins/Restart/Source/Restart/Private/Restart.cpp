// Copyright 2020 dingshukai, 577670652@qq.com . All Rights Reserved.

#include "Restart.h"
#include "RestartStyle.h"
#include "RestartCommands.h"
#include "Misc/MessageDialog.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Interfaces/IMainFrameModule.h"

#include "LevelEditor.h"

static const FName RestartTabName("Restart");

#define LOCTEXT_NAMESPACE "FRestartModule"

void FRestartModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FRestartStyle::Initialize();
	FRestartStyle::ReloadTextures();

	FRestartCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FRestartCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FRestartModule::PluginButtonClicked),
		FCanExecuteAction());

	IMainFrameModule& mainFrame = FModuleManager::Get().LoadModuleChecked<IMainFrameModule>("MainFrame");
	mainFrame.GetMainFrameCommandBindings()->Append(PluginCommands.ToSharedRef());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("FileProject", EExtensionHook::First, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FRestartModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FRestartModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
}

void FRestartModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FRestartStyle::Shutdown();

	FRestartCommands::Unregister();
}

void FRestartModule::PluginButtonClicked()
{
	FUnrealEdMisc::Get().RestartEditor(false);
}

void FRestartModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FRestartCommands::Get().PluginAction);
}

void FRestartModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FRestartCommands::Get().PluginAction);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FRestartModule, Restart)