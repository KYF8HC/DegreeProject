#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GUI/WidgetController/DP_WidgetController.h"
#include "DP_PlayerHUD.generated.h"

struct FWidgetControllerParams;
class UAttributeSet;
class UDP_UserWidgetBase;
class UDP_WidgetController;
class UAbilitySystemComponent;
class UDP_OverlayWidgetController;

UENUM(BlueprintType)
enum class EWidgetType : uint8
{
	None,
	MainMenu,
	Overlay,
	Upgrade,
	PauseMenu
};

UCLASS()
class DEGREEPROJECT_API ADP_PlayerHUD : public AHUD
{
	GENERATED_BODY()

public:
	void InitOverlay(APlayerController* PC, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	//Widget Controller Getters
	UDP_WidgetController* GetOverlayWidgetController(const FWidgetControllerParams& Params);
	UDP_WidgetController* GetUpgradeWidgetController(const FWidgetControllerParams& Params);

	//Widget Getters
	
	UDP_UserWidgetBase* GetMainMenuWidget();
	UDP_UserWidgetBase* GetOverlayWidget(const FWidgetControllerParams& Params = FWidgetControllerParams());
	UDP_UserWidgetBase* GetUpgradeWidget(const FWidgetControllerParams& Params = FWidgetControllerParams());
	UDP_UserWidgetBase* GetPauseMenuWidget();

	void ChangeWidget(EWidgetType WidgetType);

protected:
	
	//Internal Helper functions
	UDP_WidgetController* CreateWidgetController(const FWidgetControllerParams& Params, TSubclassOf<UDP_WidgetController> WidgetControllerClass);
	UDP_UserWidgetBase*  CreateWidgetHelper(const TSubclassOf<UDP_UserWidgetBase>& WidgetClass) const;
private:
#pragma region "Widgets"

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDP_UserWidgetBase> MainMenuWidgetClass{};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDP_UserWidgetBase> OverlayWidgetClass{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDP_UserWidgetBase> UpgradeWidgetClass{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDP_UserWidgetBase> PauseMenuWidgetClass{};

	UPROPERTY()
	TObjectPtr<UDP_UserWidgetBase> MainMenuWidgetRef{};
	
	UPROPERTY()
	TObjectPtr<UDP_UserWidgetBase> OverlayWidgetRef{};

	UPROPERTY()
	TObjectPtr<UDP_UserWidgetBase> UpgradeWidgetRef{};

	UPROPERTY()
	TObjectPtr<UDP_UserWidgetBase> PauseMenuWidgetRef{};

	UPROPERTY()
	TObjectPtr<UDP_UserWidgetBase> CurrentWidgetRef{};

#pragma endregion

#pragma region "Widget Controllers"

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget Controllers", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDP_WidgetController> OverlayWidgetControllerClass{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget Controllers", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDP_WidgetController> UpgradeWidgetControllerClass{};

	UPROPERTY(BlueprintReadOnly, Category = "Widget Controllers", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDP_WidgetController> OverlayWidgetControllerRef{};

	UPROPERTY(BlueprintReadOnly, Category = "Widget Controllers", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDP_WidgetController> UpgradeWidgetControllerRef{};

#pragma endregion
};
