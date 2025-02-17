#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DP_PlayerHUD.generated.h"

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

	UPROPERTY()
	TObjectPtr<UDP_UserWidgetBase> OverlayWidgetRef{};
	
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
	UDP_OverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& Params);

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDP_UserWidgetBase> OverlayWidgetClass{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget Controller", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDP_OverlayWidgetController> OverlayWidgetControllerClass{};
	
	UPROPERTY(BlueprintReadOnly, Category = "Widget Controller", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDP_OverlayWidgetController> OverlayWidgetControllerRef{};
};
