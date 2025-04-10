#include "GUI/Widgets/DP_UpgradeCardMenu.h"
#include "GUI/WidgetController/DP_UpgradeWidgetController.h"
#include "GUI/Widgets/DP_UpgradeCardWidget.h"

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
			CardWidgets[i]->SetWidgetContent(CardsInfo[i].Description, CardsInfo[i].Icon, CardsInfo[i].UpgradeCardGuid);
			//CardWidgets[i]->SetWidgetContent();	
		}
	}
}

void UDP_UpgradeCardMenu::NativePreConstruct()
{
	Super::NativePreConstruct();
	CardWidgets.Add(CardWidgetOne);
	CardWidgets.Add(CardWidgetTwo);
	CardWidgets.Add(CardWidgetThree);
}
