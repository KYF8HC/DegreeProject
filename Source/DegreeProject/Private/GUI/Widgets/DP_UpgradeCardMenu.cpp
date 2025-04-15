#include "GUI/Widgets/DP_UpgradeCardMenu.h"
#include "DP_MainEventHandlerSubsystem.h"
#include "Core/DP_GameMode.h"
#include "Core/Events/DP_EventHandler.h"
#include "GUI/HUD/DP_PlayerHUD.h"
#include "GUI/WidgetController/DP_UpgradeWidgetController.h"
#include "GUI/Widgets/DP_UpgradeCardWidget.h"

void UDP_UpgradeCardMenu::GetCardsInfo(bool bFirstTime)
{
	CardsInfo.Empty();
	UDP_UpgradeWidgetController* UpgradeWidgetController = Cast<UDP_UpgradeWidgetController>(WidgetControllerRef);
	if (UpgradeWidgetController)
	{
		CardsInfo = UpgradeWidgetController->GetNumberOfUniqueCards(CardWidgets.Num());
	}

	for (int i = 0; i < CardsInfo.Num(); ++i)
	{
		if (CardWidgets.IsValidIndex(i))
		{
			FUpgradeCardWidgetProperties WidgetProperties;
			WidgetProperties.Icon = CardsInfo[i].Icon;
			WidgetProperties.Description = CardsInfo[i].Description;
			WidgetProperties.UpgradeCardType = CardsInfo[i].UpgradeCardType;
			WidgetProperties.UpgradeCardGuid = CardsInfo[i].UpgradeCardGuid;
			CardWidgets[i]->SetWidgetProperties(WidgetProperties);
		}
	}
}

void UDP_UpgradeCardMenu::OnBegin(bool bFirstTime)
{
	Super::OnBegin(bFirstTime);
	if (bFirstTime)
	{
		for (UDP_UpgradeCardWidget* CardWidget : CardWidgets)
		{
			if (CardWidget)
			{
				CardWidget->OnButtonClickedDelegate.AddDynamic(this, &UDP_UpgradeCardMenu::ChoseUpgrade);
			}
		}
	}
	GetCardsInfo(bFirstTime);
}

void UDP_UpgradeCardMenu::OnEnd()
{
	Super::OnEnd();

	GetGameInstance()->GetSubsystem<UDP_MainEventHandlerSubsystem>()->GetMainEventHandler()->PushEvent
		(Cast<ADP_GameMode>(GetWorld()->GetAuthGameMode()));
	PlayerHUDRef->ChangeWidget(EWidgetType::Overlay);
}

void UDP_UpgradeCardMenu::ChoseUpgrade(const FGuid& UniqueIdentifier, EUpgradeCardType CardType)
{
	UDP_UpgradeWidgetController* UpgradeWidgetController = Cast<UDP_UpgradeWidgetController>(WidgetControllerRef);
	if (UpgradeWidgetController)
	{
		UpgradeWidgetController->GrantUpgrade(UniqueIdentifier, CardType);
	}
	bIsDone = true;
}


void UDP_UpgradeCardMenu::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (CardWidgets.Num() > 0)
		return;

	CardWidgets.Add(CardWidgetOne);
	CardWidgets.Add(CardWidgetTwo);
	CardWidgets.Add(CardWidgetThree);
}

void UDP_UpgradeCardMenu::NativeConstruct()
{
	Super::NativeConstruct();

	bIsDone = false;
	GetGameInstance()->GetSubsystem<UDP_MainEventHandlerSubsystem>()->GetMainEventHandler()->PushEvent(this);
}
