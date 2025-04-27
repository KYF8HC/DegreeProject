#include "GUI/Widgets/DP_UpgradeCardMenu.h"
#include "DP_MainEventHandlerSubsystem.h"
#include "Core/Events/DP_EventHandler.h"
#include "GUI/WidgetController/DP_UpgradeWidgetController.h"
#include "GUI/Widgets/DP_UpgradeCardWidget.h"
#include "Player/DP_PlayerController.h"

void UDP_UpgradeCardMenu::GetCardsInfo()
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

	EnableWidget(true);
	
	if (bFirstTime)
	{
		for (UDP_UpgradeCardWidget* CardWidget : CardWidgets)
		{
			if (CardWidget->OnButtonClickedDelegate.IsBound())
				continue;
			
			if (CardWidget)
			{
				CardWidget->OnButtonClickedDelegate.AddDynamic(this, &UDP_UpgradeCardMenu::ChoseUpgrade);
			}
		}
	}
	GetCardsInfo();
}

void UDP_UpgradeCardMenu::OnEnd()
{
	Super::OnEnd();
	EnableWidget(false);
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
	ADP_PlayerController* PlayerController = Cast<ADP_PlayerController>(GetOwningPlayer());
	PlayerController->SetPause(true);
	PlayerController->SetCanReceiveInput(false);
}
