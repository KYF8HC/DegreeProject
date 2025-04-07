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
	OverlayWidgetControllerRef = GetOverlayWidgetController(Params);
	
	OverlayWidgetRef->SetWidgetController(OverlayWidgetControllerRef);
	OverlayWidgetControllerRef->BroadcastInitialValues();

	
	//Widget->AddToViewport();

	//TODO: JUST FOR TESTING
	UUserWidget* UserWidget = CreateWidget<UUserWidget>(GetWorld(), UpgradeWidgetClass);
	UpgradeWidgetRef = Cast<UDP_UserWidgetBase>(UserWidget);
	UpgradeWidgetControllerRef = GetUpgradeWidgetController(Params);
	UpgradeWidgetRef->SetWidgetController(UpgradeWidgetControllerRef);
	UpgradeWidgetRef->AddToViewport();
}

UDP_WidgetController* ADP_PlayerHUD::GetOverlayWidgetController(const FWidgetControllerParams& Params)
{
	if (OverlayWidgetControllerRef == nullptr)
	{
		OverlayWidgetControllerRef = NewObject<UDP_WidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetControllerRef->SetWidgetControllerParams(Params);
		OverlayWidgetControllerRef->BindCallbacksToDependencies();
	}

	return OverlayWidgetControllerRef;
}

UDP_WidgetController* ADP_PlayerHUD::GetUpgradeWidgetController(const FWidgetControllerParams& Params)
{
	if (UpgradeWidgetControllerRef == nullptr)
	{
		UpgradeWidgetControllerRef = NewObject<UDP_WidgetController>(this, UpgradeWidgetControllerClass);
		UpgradeWidgetControllerRef->SetWidgetControllerParams(Params);
		UpgradeWidgetControllerRef->BindCallbacksToDependencies();
	}

	return UpgradeWidgetControllerRef;
}