#include "GUI/Widgets/DP_UpgradeCardWidget.h"

void UDP_UpgradeCardWidget::SetWidgetContent(const FText& DescText, UTexture2D* Icon, const FGuid UniqueIdentifier)
{
	CardDescText = DescText;
	ImageIcon = Icon;
	CardGuid = UniqueIdentifier;
	OnWidgetContentSet();
}
