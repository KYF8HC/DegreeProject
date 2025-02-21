#include "GUI/HUD/DP_PlayerHUD.h"
#include "GUI/WidgetController/DP_OverlayWidgetController.h"
#include "GUI/Widgets/DP_UserWidgetBase.h"

void ADP_PlayerHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC,
                                UAttributeSet* AS)
{
	checkf(OverlayWidgetClass,
		TEXT("ADP_PlayerHUD::InitOverlay: OverlayWidgetClass is not set in %s"), *GetName());

	checkf(OverlayWidgetControllerClass,
	       TEXT("ADP_PlayerHUD::InitOverlay: OverlayWidgetControllerClass is not set in %s"), *GetName());


	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidgetRef = Cast<UDP_UserWidgetBase>(Widget);

	const FWidgetControllerParams Params(PC, PS, ASC, AS);
	UDP_OverlayWidgetController* WidgetControllerRef = GetOverlayWidgetController(Params);
	
	OverlayWidgetRef->SetWidgetController(WidgetControllerRef);
	WidgetControllerRef->BroadcastInitialValues();	
	Widget->AddToViewport();
}

UDP_OverlayWidgetController* ADP_PlayerHUD::GetOverlayWidgetController(const FWidgetControllerParams& Params)
{
	if (OverlayWidgetControllerRef == nullptr)
	{
		OverlayWidgetControllerRef = NewObject<UDP_OverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetControllerRef->SetWidgetControllerParams(Params);
		OverlayWidgetControllerRef->BindCallbacksToDependencies();
	}

	return OverlayWidgetControllerRef;
}
