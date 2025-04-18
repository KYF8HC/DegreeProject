﻿#include "GUI/Widgets/DP_MainMenuWidget.h"
#include "DP_MainEventHandlerSubsystem.h"
#include "Core/Events/DP_EventHandler.h"
#include "GUI/HUD/DP_PlayerHUD.h"
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
	PlayerHUDRef->ChangeWidget(EWidgetType::Upgrade);
	//CreateAndPushEventWidget<UDP_UpgradeCardMenu>(GetGameInstance(), UpgradeWidgetClass,TEXT("UpgradeCardMenu"));
}

void UDP_MainMenuWidget::OnBegin(bool bFirstTime)
{
	Super::OnBegin(bFirstTime);
	//EnableWidget(true);
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
