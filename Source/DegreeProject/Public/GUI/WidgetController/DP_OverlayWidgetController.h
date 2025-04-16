#pragma once

#include "CoreMinimal.h"
#include "DP_WidgetController.h"
#include "DP_OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChange, float, NewValue);

class UDP_UpgradeCardInfo;
class UGameplayAbility;
struct FOnAttributeChangeData;

UCLASS(BlueprintType, Blueprintable)
class DEGREEPROJECT_API UDP_OverlayWidgetController : public UDP_WidgetController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChange OnHealthChange{};

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChange OnMaxHealthChange{};

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChange OnAbilityResourceChange{};

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChange OnMaxAbilityResourceChange{};

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChange OnExperiencePercentageChange{};
	
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
	virtual void InitializeWidgetController() override;

protected:

	void HealthChanged(const FOnAttributeChangeData& Data);
	void MaxHealthChanged(const FOnAttributeChangeData& Data);
	void AbilityResourceChanged(const FOnAttributeChangeData& Data);
	void MaxAbilityResourceChanged(const FOnAttributeChangeData& Data);
	void OnExperiencePointsChanged(const int32 NewExperiencePoints) const;
	void OnLevelChanged(const int32 NewLevel);

};