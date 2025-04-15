#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DP_UserWidgetBase.generated.h"


class ADP_PlayerHUD;

UCLASS()
class DEGREEPROJECT_API UDP_UserWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category= "Widget Controller")
	TObjectPtr<UObject> WidgetControllerRef{};

	UFUNCTION(BlueprintCallable)
	virtual void SetWidgetController(UObject* InControllerRef);

	UFUNCTION(BlueprintCallable)
	void EnableWidget(bool bEnable);

	FORCEINLINE void SetPlayerHUDRef(ADP_PlayerHUD* InPlayerHUDRef) { PlayerHUDRef = InPlayerHUDRef; }

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ADP_PlayerHUD> PlayerHUDRef{};

	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetControllerSet();
};
