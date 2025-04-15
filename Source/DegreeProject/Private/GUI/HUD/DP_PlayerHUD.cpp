#include "GUI/HUD/DP_PlayerHUD.h"
#include "GUI/WidgetController/DP_OverlayWidgetController.h"
#include "GUI/Widgets/DP_UserWidgetBase.h"

void ADP_PlayerHUD::InitOverlay(APlayerController* PC, UAbilitySystemComponent* ASC,
                                UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("ADP_PlayerHUD::InitOverlay: OverlayWidgetClass is not set in %s"), *GetName());
	checkf(OverlayWidgetControllerClass,
	       TEXT("ADP_PlayerHUD::InitOverlay: OverlayWidgetControllerClass is not set in %s"), *GetName());
	checkf(UpgradeWidgetClass, TEXT("ADP_PlayerHUD::InitOverlay: UpgradeWidgetClass is not set in %s"), *GetName());
	checkf(UpgradeWidgetControllerClass,
	       TEXT("ADP_PlayerHUD::InitOverlay: UpgradeWidgetControllerClass is not set in %s"), *GetName());
	checkf(PauseMenuWidgetClass, TEXT("ADP_PlayerHUD::InitOverlay: PauseMenuWidgetClass is not set in %s"), *GetName());

	FWidgetControllerParams Params = FWidgetControllerParams(PC, ASC, AS);
	
	GetOverlayWidget(Params)->SetPlayerHUDRef(this);
	GetUpgradeWidget(Params)->SetPlayerHUDRef(this);
	GetPauseMenuWidget()->SetPlayerHUDRef(this);
	GetMainMenuWidget()->SetPlayerHUDRef(this);
	
	CurrentWidgetRef = MainMenuWidgetRef;
	CurrentWidgetRef->EnableWidget(true);
}


#pragma region "Widget Getters"
UDP_UserWidgetBase* ADP_PlayerHUD::GetOverlayWidget(const FWidgetControllerParams& Params)
{
	if (OverlayWidgetRef == nullptr)
	{
		OverlayWidgetRef = CreateWidgetHelper(OverlayWidgetClass);
		OverlayWidgetRef->SetWidgetController(GetOverlayWidgetController(Params));
	}

	return OverlayWidgetRef;
}

UDP_UserWidgetBase* ADP_PlayerHUD::GetUpgradeWidget(const FWidgetControllerParams& Params)
{
	if (UpgradeWidgetRef == nullptr)
	{
		UpgradeWidgetRef = CreateWidgetHelper(UpgradeWidgetClass);
		UpgradeWidgetRef->SetWidgetController(GetUpgradeWidgetController(Params));
	}

	return UpgradeWidgetRef;
}


UDP_UserWidgetBase* ADP_PlayerHUD::GetMainMenuWidget()
{
	if (MainMenuWidgetRef == nullptr)
		MainMenuWidgetRef = CreateWidgetHelper(MainMenuWidgetClass);

	return MainMenuWidgetRef;
}

UDP_UserWidgetBase* ADP_PlayerHUD::GetPauseMenuWidget()
{
	if (PauseMenuWidgetRef == nullptr)
		PauseMenuWidgetRef = CreateWidgetHelper(PauseMenuWidgetClass);

	return PauseMenuWidgetRef;
}

void ADP_PlayerHUD::ChangeWidget(EWidgetType WidgetType)
{

	if (CurrentWidgetRef != nullptr)
		CurrentWidgetRef->EnableWidget(false);
	
	switch (WidgetType)
	{
		case EWidgetType::MainMenu:
			CurrentWidgetRef = GetMainMenuWidget();
			break;
		case EWidgetType::Overlay:
			CurrentWidgetRef = GetOverlayWidget();
			break;
		case EWidgetType::Upgrade:
			CurrentWidgetRef = GetUpgradeWidget();
			break;
		case EWidgetType::PauseMenu:
			CurrentWidgetRef = GetPauseMenuWidget();
			break;
		default:
			CurrentWidgetRef = nullptr;
			break;
	}

	if (CurrentWidgetRef != nullptr)
		CurrentWidgetRef->EnableWidget(true);
}

UDP_UserWidgetBase* ADP_PlayerHUD::CreateWidgetHelper(const TSubclassOf<UDP_UserWidgetBase>& WidgetClass) const
{
	if (!WidgetClass) return nullptr;

	UDP_UserWidgetBase* UserWidget = CreateWidget<UDP_UserWidgetBase>(GetWorld(), WidgetClass);
	return UserWidget;
}

#pragma endregion

#pragma region "Widget Controller Getters"
UDP_WidgetController* ADP_PlayerHUD::GetOverlayWidgetController(const FWidgetControllerParams& Params)
{
	if (OverlayWidgetControllerRef == nullptr)
	{
		OverlayWidgetControllerRef = CreateWidgetController(Params, OverlayWidgetControllerClass);
	}
	return OverlayWidgetControllerRef;
}

UDP_WidgetController* ADP_PlayerHUD::GetUpgradeWidgetController(const FWidgetControllerParams& Params)
{
	if (UpgradeWidgetControllerRef == nullptr)
	{
		UpgradeWidgetControllerRef = CreateWidgetController(Params, UpgradeWidgetControllerClass);
	}
	return UpgradeWidgetControllerRef;
}

UDP_WidgetController* ADP_PlayerHUD::CreateWidgetController(const FWidgetControllerParams& Params,
                                                            TSubclassOf<UDP_WidgetController> WidgetControllerClass)
{
	UDP_WidgetController* WidgetController = NewObject<UDP_WidgetController>(this, WidgetControllerClass);
	WidgetController->SetWidgetControllerParams(Params);
	WidgetController->BindCallbacksToDependencies();
	return WidgetController;
}
#pragma endregion
