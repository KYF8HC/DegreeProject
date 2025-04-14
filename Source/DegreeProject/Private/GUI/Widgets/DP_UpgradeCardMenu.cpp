#include "GUI/Widgets/DP_UpgradeCardMenu.h"

#include "Core/DP_GameMode.h"
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
		
		auto WidgetController = NewObject<UDP_WidgetController>(this, WidgetControllerClass);
		WidgetController->SetWidgetControllerParams(Cast<ADP_GameMode>(GetWorld()->GetAuthGameMode())->WidgetControllerParams);
		WidgetController->BindCallbacksToDependencies();
		WidgetControllerRef = WidgetController;
		
		for (UDP_UpgradeCardWidget* CardWidget : CardWidgets)
		{
			if (CardWidget)
			{
				CardWidget->OnButtonClickedDelegate.AddDynamic(this, &UDP_UpgradeCardMenu::ChoseUpgrade);
			}
		}
	}
	GetCardsInfo(bFirstTime);
	EnableWidget(true);
}

void UDP_UpgradeCardMenu::ChoseUpgrade(const FGuid& UniqueIdentifier, EUpgradeCardType CardType)
{
	UDP_UpgradeWidgetController* UpgradeWidgetController = Cast<UDP_UpgradeWidgetController>(WidgetControllerRef);
	if (UpgradeWidgetController)
	{
		UpgradeWidgetController->GrantUpgrade(UniqueIdentifier, CardType);
	}
}


void UDP_UpgradeCardMenu::NativePreConstruct()
{
	Super::NativePreConstruct();
	CardWidgets.Add(CardWidgetOne);
	CardWidgets.Add(CardWidgetTwo);
	CardWidgets.Add(CardWidgetThree);
}
