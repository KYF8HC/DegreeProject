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
enum class EUpgradeCardType : uint8
{
	Weapon,
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGuid UpgradeCardGuid{};
};

UCLASS()
class DEGREEPROJECT_API UDP_UpgradeCardInfo : public UDataAsset, public FAsyncMixin
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FUpgradeCardInfo> UpgradeCardInfoArray{};

	FUpgradeCardInfo FindUpgradeCardInfoForTag(const FGameplayTag& WeaponTag, bool bLogNotFound) const;
	void LoadWeaponClassByGuidAsync(const FGuid& UniqueIdentifier, TFunction<void(const FGameplayTag&, const TSubclassOf<UGameplayAbility>&)> Callback);
	void LoadEffectClassByGuidAsync(const FGuid& UniqueIdentifier, TFunction<void(const TSubclassOf<UGameplayEffect>&)> Callback);
	TArray<FUpgradeCardInfo> GetNumberOfUniqueCards(int NumberOfCards) const;

	
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
};
