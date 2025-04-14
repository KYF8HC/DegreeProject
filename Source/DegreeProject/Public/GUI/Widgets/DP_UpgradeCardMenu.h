#pragma once

#include "CoreMinimal.h"
#include "DP_EventUserWidgetBase.h"
#include "DP_UpgradeCardMenu.generated.h"


class UDP_WidgetController;
enum class EUpgradeCardType : uint8;
struct FUpgradeCardInfo;
class UDP_UpgradeCardWidget;

UCLASS()
class DEGREEPROJECT_API UDP_UpgradeCardMenu : public UDP_EventUserWidgetBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "UpgradeCardMenu")
	void GetCardsInfo(bool bFirstTime);

	virtual void OnBegin(bool bFirstTime) override;

protected:

	
	UFUNCTION()
	void ChoseUpgrade(const FGuid& UniqueIdentifier, EUpgradeCardType CardType);
	virtual void NativePreConstruct() override;

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "UpgradeCardMenu")
	TSubclassOf<UDP_WidgetController> WidgetControllerClass{};

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
