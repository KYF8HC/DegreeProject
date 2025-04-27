#pragma once

#include "CoreMinimal.h"
#include "AsyncMixin.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DP_UpgradeCardInfo.generated.h"

class UGameplayEffect;
class UGameplayAbility;
class UTexture2D;

UENUM(BlueprintType)
enum class ECardRarity : uint8
{
	Common,
	Rare,
	Epic,
	Legendary
};

UENUM(BlueprintType)
enum class EUpgradeCardType : uint8
{
	Weapon,
	WeaponUpgrade,
	Ability,
	Effect,
	None
};

USTRUCT(BlueprintType)
struct FUpgradeCardInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AbilityTag{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTexture2D> Icon{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Description{};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EUpgradeCardType UpgradeCardType{EUpgradeCardType::None};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ECardRarity CardRarity{ECardRarity::Common};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<UGameplayAbility> AbilityClass{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<UGameplayEffect> EffectClass{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGuid UpgradeCardGuid{};
};

USTRUCT(BlueprintType)
struct FUpgradeCardWidgetProperties
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTexture2D> Icon{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Description{};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EUpgradeCardType UpgradeCardType{EUpgradeCardType::None};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ECardRarity CardRarity{ECardRarity::Common};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGuid UpgradeCardGuid{};
};

UCLASS()
class DEGREEPROJECT_API UDP_UpgradeCardInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FUpgradeCardInfo> UpgradeCardInfoArray{};

	FUpgradeCardInfo FindUpgradeCardInfoForTag(const FGameplayTag& WeaponTag, bool bLogNotFound) const;
	void LoadWeaponClassByGuidAsync(const FGuid& UniqueIdentifier, TFunction<void(const FGameplayTag&, const TSubclassOf<UGameplayAbility>&)> Callback);
	void LoadEffectClassByGuidAsync(const FGuid& UniqueIdentifier, TFunction<void(const TSubclassOf<UGameplayEffect>&)> Callback);
	TArray<FUpgradeCardInfo> GetNumberOfUniqueCards(const int NumberOfCards, const int PlayerLevel, const FGameplayTagContainer& OwnedWeapons) const;

	
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

private:
	bool ShouldIncludeCard(const FUpgradeCardInfo& Info, int PlayerLevel, const FGameplayTagContainer& OwnedWeapons) const;
	bool CheckRarity(const FUpgradeCardInfo& Info) const;
};
