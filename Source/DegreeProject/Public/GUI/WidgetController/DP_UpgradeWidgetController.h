#pragma once

#include "CoreMinimal.h"
#include "DP_WidgetController.h"
#include "GameplayTagContainer.h"
#include "DP_UpgradeWidgetController.generated.h"

class UGameplayAbility;
class UDP_UpgradeCardInfo;

UCLASS(BlueprintType, Blueprintable)
class DEGREEPROJECT_API UDP_UpgradeWidgetController : public UDP_WidgetController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void GivePlayerWeaponByTag(const FGameplayTag& WeaponTag);

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToPlayer(const FGuid& UniqueIdentifier) const;
	virtual void InitializeWidgetController() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon Info")
	TObjectPtr<UDP_UpgradeCardInfo> WeaponInfo{};

	void GivePlayerWeaponInternal(const FGameplayTag& WeaponTag,
	                              const TSubclassOf<UGameplayAbility>& WeaponClass) const;
};
