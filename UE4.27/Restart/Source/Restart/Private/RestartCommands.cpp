// Copyright 2020 dingshukai, 577670652@qq.com . All Rights Reserved.

#include "RestartCommands.h"

#define LOCTEXT_NAMESPACE "FRestartModule"

void FRestartCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "Restart", "Execute Restart action", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control|EModifierKey::Alt, EKeys::R));
}

#undef LOCTEXT_NAMESPACE
