#pragma once

#include "CoreMinimal.h"
#include "DP_WidgetController.h"
#include "DP_OverlayWidgetController.generated.h"

struct FOnAttributeChangeData;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChange, float, NewValue);

UCLASS(BlueprintType, Blueprintable)
class DEGREEPROJECT_API UDP_OverlayWidgetController : public UDP_WidgetController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChange OnHealthChange;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChange OnMaxHealthChange;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChange OnAbilityResourceChange;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChange OnMaxAbilityResourceChange;

	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
protected:

	void HealthChanged(const FOnAttributeChangeData& Data);
	void MaxHealthChanged(const FOnAttributeChangeData& Data);
	void AbilityResourceChanged(const FOnAttributeChangeData& Data);
	void MaxAbilityResourceChanged(const FOnAttributeChangeData& Data);
};
