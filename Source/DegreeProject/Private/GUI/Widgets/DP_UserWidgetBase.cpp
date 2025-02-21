#include "GUI/Widgets/DP_UserWidgetBase.h"

void UDP_UserWidgetBase::SetWidgetController(UObject* InControllerRef)
{
	WidgetControllerRef = InControllerRef;
	OnWidgetControllerSet();
}

void UDP_UserWidgetBase::EnableWidget(bool bEnable)
{
	if (bEnable)
	{
		AddToViewport();
		UE_LOG(LogTemp, Log, TEXT("%s added to viewport"), *GetName());
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("%s removed from viewport"), *GetName());
		RemoveFromParent();
	}
}