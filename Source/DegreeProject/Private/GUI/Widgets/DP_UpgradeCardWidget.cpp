#include "GUI/Widgets/DP_UpgradeCardWidget.h"

void UDP_UpgradeCardWidget::SetWidgetProperties(const FUpgradeCardWidgetProperties& WidgetProperties)
{
	CardDescText = WidgetProperties.Description;
	ImageIcon = WidgetProperties.Icon;
	CardType = WidgetProperties.UpgradeCardType;
	CardGuid = WidgetProperties.UpgradeCardGuid;
	OnWidgetPropertiesSet();
}
