#pragma once

#include "CoreMinimal.h"
#include "AsyncMixin.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DP_WeaponInfo.generated.h"

class UGameplayAbility;
class UTexture2D;

USTRUCT(BlueprintType)
struct FWeaponInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AbilityTag{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const UTexture2D> Icon{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<UGameplayAbility> AbilityClass{};
};

UCLASS()
class DEGREEPROJECT_API UDP_WeaponInfo : public UDataAsset, public FAsyncMixin
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FWeaponInfo> WeaponInfoArray{};

	FWeaponInfo FindWeaponInfoForTag(const FGameplayTag& WeaponTag, bool bLogNotFound) const;
	void FindAbilityClassByTagAsync(const FGameplayTag& WeaponTag, TFunction<void(const FGameplayTag&, const TSubclassOf<UGameplayAbility>&)> Callback);
};
