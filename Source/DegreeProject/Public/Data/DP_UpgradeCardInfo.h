#pragma once

#include "CoreMinimal.h"
#include "AsyncMixin.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DP_UpgradeCardInfo.generated.h"

class UGameplayEffect;
class UGameplayAbility;
class UTexture2D;

USTRUCT(BlueprintType)
struct FUpgradeCardInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AbilityTag{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const UTexture2D> Icon{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Description{};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<UGameplayAbility> AbilityClass{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<UGameplayEffect> EffectClass{};

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
	void FindAbilityClassByTagAsync(const FGameplayTag& WeaponTag, TFunction<void(const FGameplayTag&, const TSubclassOf<UGameplayAbility>&)> Callback);
	void FindEffectClassByUniqueIdentifierAsync(const FGuid& UniqueIdentifier, TFunction<void(const TSubclassOf<UGameplayEffect>&)> Callback);

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
};
