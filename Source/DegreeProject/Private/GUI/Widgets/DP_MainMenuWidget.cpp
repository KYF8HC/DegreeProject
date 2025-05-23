﻿#include "GUI/Widgets/DP_MainMenuWidget.h"
#include "DP_MainEventHandlerSubsystem.h"
#include "Core/DP_GameMode.h"
#include "Core/Events/DP_EventHandler.h"
#include "GUI/Widgets/DP_UpgradeCardMenu.h"

void UDP_MainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UDP_EventHandler* MainEventHandler = GetGameInstance()->GetSubsystem<UDP_MainEventHandlerSubsystem>()->
	                                                        GetMainEventHandler();
	MainEventHandler->PushEvent(this);
}

void UDP_MainMenuWidget::OnStartGame()
{
	GetGameInstance()->GetSubsystem<UDP_MainEventHandlerSubsystem>()->GetMainEventHandler()->PushEvent
		(Cast<ADP_GameMode>(GetWorld()->GetAuthGameMode()));
}

void UDP_MainMenuWidget::OnBegin(bool bFirstTime)
{
	Super::OnBegin(bFirstTime);
}

void UDP_MainMenuWidget::OnEnd()
{
	Super::OnEnd();
	EnableWidget(false);
}

bool UDP_MainMenuWidget::IsDone()
{
	return false;
}
