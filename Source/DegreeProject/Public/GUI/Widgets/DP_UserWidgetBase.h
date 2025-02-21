#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DP_UserWidgetBase.generated.h"


UCLASS()
class DEGREEPROJECT_API UDP_UserWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadOnly, Category= "Widget Controller")
	TObjectPtr<UObject> WidgetControllerRef{};
	
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InControllerRef);

	UFUNCTION(BlueprintCallable)
	void EnableWidget(bool bEnable);
	
protected:

	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetControllerSet();
};
