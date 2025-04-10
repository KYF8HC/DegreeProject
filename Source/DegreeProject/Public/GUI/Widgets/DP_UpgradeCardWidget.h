#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DP_UpgradeCardWidget.generated.h"

UCLASS()
class DEGREEPROJECT_API UDP_UpgradeCardWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetContentSet();
	
	void SetWidgetContent(const FText& DescText, UTexture2D* Icon, FGuid UniqueIdentifier);

protected:

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "UpgradeCard")
	FText CardDescText{};
	
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "UpgradeCard")
	TObjectPtr<UTexture2D> ImageIcon{};
	
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "UpgradeCard")
	FGuid CardGuid{};
};
