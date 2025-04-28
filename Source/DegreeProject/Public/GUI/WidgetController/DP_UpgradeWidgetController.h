#pragma once

#include "CoreMinimal.h"
#include "DP_WidgetController.h"
#include "GameplayTagContainer.h"
#include "Data/DP_UpgradeCardInfo.h"
#include "DP_UpgradeWidgetController.generated.h"

class UGameplayEffect;
class UGameplayAbility;

UCLASS(BlueprintType, Blueprintable)
class DEGREEPROJECT_API UDP_UpgradeWidgetController : public UDP_WidgetController
{
	GENERATED_BODY()

public:
	void GrantUpgrade(FGuid UniqueIdentifier, EUpgradeCardType CardType);
	TArray<FUpgradeCardInfo> GetNumberOfUniqueCards(int NumberOfCards) const;
	virtual void InitializeWidgetController() override;

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon Info")
	TObjectPtr<UDP_UpgradeCardInfo> UpgradeCardInfo{};

	void GiveWeaponToPlayerCallback(const FGameplayTag& WeaponTag,
	                                const TSubclassOf<UGameplayAbility>& WeaponClass) const;
	void ApplyEffectToPlayerCallback(const FGameplayTag& AttributeTag, const ECardRarity CardRarity, const TSubclassOf<UGameplayEffect>& EffectClass) const;
};
