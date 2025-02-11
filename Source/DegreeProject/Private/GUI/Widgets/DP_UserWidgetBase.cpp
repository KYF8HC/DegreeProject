#include "GUI/Widgets/DP_UserWidgetBase.h"

void UDP_UserWidgetBase::SetWidgetController(UObject* InControllerRef)
{
	WidgetControllerRef = InControllerRef;
	OnWidgetControllerSet();
}
