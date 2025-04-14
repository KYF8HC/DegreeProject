#pragma once

#include "CoreMinimal.h"
#include "DP_EventUserWidgetBase.h"
#include "DP_MainMenuWidget.generated.h"

class UDP_UpgradeCardMenu;

UCLASS()
class DEGREEPROJECT_API UDP_MainMenuWidget : public UDP_EventUserWidgetBase
{
	GENERATED_BODY()

public:
	virtual void OnBegin(bool bFirstTime) override;
	virtual void OnEnd() override;
	virtual bool IsDone() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDP_UpgradeCardMenu> UpgradeWidgetClass;
	
	virtual void NativeConstruct() override;

private:
	UFUNCTION(BlueprintCallable)
	void OnStartGame();
};
