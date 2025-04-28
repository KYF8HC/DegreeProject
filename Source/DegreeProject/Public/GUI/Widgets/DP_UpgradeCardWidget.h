#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/DP_UpgradeCardInfo.h"
#include "DP_UpgradeCardWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonClicked, const FGuid&, UniqueIdentifier, EUpgradeCardType, CardType);

UCLASS()
class DEGREEPROJECT_API UDP_UpgradeCardWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "UpgradeCard")
	FOnButtonClicked OnButtonClickedDelegate{};
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetPropertiesSet();
	
	void SetWidgetProperties(const FUpgradeCardWidgetProperties& WidgetProperties);

protected:

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "UpgradeCard")
	FText CardDescText{};
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "UpgradeCard")
	TObjectPtr<UTexture2D> ImageIcon{};

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "UpgradeCard")
	EUpgradeCardType CardType{EUpgradeCardType::None};
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "UpgradeCard")
	FGuid CardGuid{};

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "UpgradeCard")
	ECardRarity CardRarity{ECardRarity::Common};
};
