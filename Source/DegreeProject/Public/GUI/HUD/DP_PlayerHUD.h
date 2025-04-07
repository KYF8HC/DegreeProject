#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DP_PlayerHUD.generated.h"

class UDP_WidgetController;
struct FWidgetControllerParams;
class UAttributeSet;
class UDP_UserWidgetBase;
class UAbilitySystemComponent;
class UDP_OverlayWidgetController;

UCLASS()
class DEGREEPROJECT_API ADP_PlayerHUD : public AHUD
{
	GENERATED_BODY()

public:
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
	UDP_WidgetController* GetOverlayWidgetController(const FWidgetControllerParams& Params);
	UDP_WidgetController* GetUpgradeWidgetController(const FWidgetControllerParams& Params);

private:

#pragma region "Widgets"
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDP_UserWidgetBase> OverlayWidgetClass{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDP_UserWidgetBase> UpgradeWidgetClass{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDP_UserWidgetBase> MainMenuWidgetClass{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDP_UserWidgetBase> PauseMenuWidgetClass{};
	
	UPROPERTY()
	TObjectPtr<UDP_UserWidgetBase> OverlayWidgetRef{};

	UPROPERTY()
	TObjectPtr<UDP_UserWidgetBase> UpgradeWidgetRef{};

	UPROPERTY()
	TObjectPtr<UDP_UserWidgetBase> MainMenuWidgetRef{};

	UPROPERTY()
	TObjectPtr<UDP_UserWidgetBase> PauseMenuWidgetRef{};

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
