#pragma once

#include "CoreMinimal.h"
#include "DP_WidgetController.h"
#include "GameplayTagContainer.h"
#include "DP_UpgradeWidgetController.generated.h"

struct FUpgradeCardInfo;
class UGameplayEffect;
class UGameplayAbility;
class UDP_UpgradeCardInfo;

UCLASS(BlueprintType, Blueprintable)
class DEGREEPROJECT_API UDP_UpgradeWidgetController : public UDP_WidgetController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void GiveWeaponToPlayer(const FGuid& UniqueIdentifier);

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToPlayer(const FGuid& UniqueIdentifier);

	TArray<FUpgradeCardInfo> GetNumberOfUniqueCards(int NumberOfCards) const;
	
	virtual void InitializeWidgetController() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon Info")
	TObjectPtr<UDP_UpgradeCardInfo> UpgradeCardInfo{};

	void GiveWeaponToPlayerInternal(const FGameplayTag& WeaponTag,
	                              const TSubclassOf<UGameplayAbility>& WeaponClass) const;
	void ApplyEffectToPlayerInternal(const TSubclassOf<UGameplayEffect>& EffectClass) const;
};
