// Copyright 2020 dingshukai, 577670652@qq.com . All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "RestartStyle.h"

class FRestartCommands : public TCommands<FRestartCommands>
{
public:

	FRestartCommands()
		: TCommands<FRestartCommands>(TEXT("Restart"), NSLOCTEXT("Contexts", "Restart", "Restart Plugin"), NAME_None, FRestartStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
