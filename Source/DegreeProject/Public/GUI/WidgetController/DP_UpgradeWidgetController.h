#pragma once

#include "CoreMinimal.h"
#include "DP_WidgetController.h"
#include "GameplayTagContainer.h"
#include "DP_UpgradeWidgetController.generated.h"

class UGameplayAbility;
class UDP_WeaponInfo;

UCLASS(BlueprintType, Blueprintable)
class DEGREEPROJECT_API UDP_UpgradeWidgetController : public UDP_WidgetController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void GivePlayerWeaponByTag(const FGameplayTag& WeaponTag);
	virtual void InitializeWidgetController() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon Info")
	TObjectPtr<UDP_WeaponInfo> WeaponInfo{};

	void GivePlayerWeaponInternal(const FGameplayTag& WeaponTag,
	                              const TSubclassOf<UGameplayAbility>& WeaponClass) const;
};
