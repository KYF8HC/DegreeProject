#pragma once

#include "CoreMinimal.h"
#include "DP_UserWidgetBase.h"
#include "Data/DP_UpgradeCardInfo.h"
#include "DP_UpgradeCardMenu.generated.h"


class UDP_UpgradeCardWidget;

UCLASS()
class DEGREEPROJECT_API UDP_UpgradeCardMenu : public UDP_UserWidgetBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "UpgradeCardMenu")
	void GetCardsInfo();

protected:
	virtual void NativePreConstruct() override;

private:

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "UpgradeCardMenu")
	TArray<FUpgradeCardInfo> CardsInfo{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "UpgradeCardMenu")
	TArray<UDP_UpgradeCardWidget*> CardWidgets{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UpgradeCardMenu", meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UDP_UpgradeCardWidget> CardWidgetOne{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UpgradeCardMenu", meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UDP_UpgradeCardWidget> CardWidgetTwo{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UpgradeCardMenu", meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UDP_UpgradeCardWidget> CardWidgetThree{};
};
