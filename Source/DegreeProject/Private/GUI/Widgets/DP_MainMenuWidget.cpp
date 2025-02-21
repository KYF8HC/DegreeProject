#include "GUI/Widgets/DP_MainMenuWidget.h"
#include "DP_MainEventHandlerSubsystem.h"
#include "Core/DP_GameMode.h"
#include "Core/Events/DP_EventHandler.h"

void UDP_MainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UDP_EventHandler* MainEventHandler = GetGameInstance()->GetSubsystem<UDP_MainEventHandlerSubsystem>()->
	                                                        GetMainEventHandler();
	MainEventHandler->PushEvent(this);
}

void UDP_MainMenuWidget::OnStartGame()
{
	UDP_EventHandler* MainEventHandler = GetGameInstance()->GetSubsystem<UDP_MainEventHandlerSubsystem>()->
														GetMainEventHandler();
	MainEventHandler->PushEvent(Cast<ADP_GameMode>(GetWorld()->GetAuthGameMode()));
}
