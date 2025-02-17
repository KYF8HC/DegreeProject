#include "GUI/WidgetController/DP_WidgetController.h"

void UDP_WidgetController::SetWidgetControllerParams(const FWidgetControllerParams& Params)
{
	PlayerControllerRef = Params.PlayerController;
	PlayerStateRef = Params.PlayerState;
	AbilitySystemComponentRef = Params.AbilitySystemComponent;
	AttributeSetRef = Params.AttributeSet;
}

void UDP_WidgetController::BroadcastInitialValues()
{
	
}

void UDP_WidgetController::BindCallbacksToDependencies()
{
	
}
