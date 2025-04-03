#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DP_WeaponInfo.generated.h"

class UTexture2D;

USTRUCT(BlueprintType)
struct FDP_WeaponInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AbilityTag{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const UTexture2D> Icon{};
};

UCLASS()
class DEGREEPROJECT_API UDP_WeaponInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FDP_WeaponInfo> WeaponInfoArray{};

	FDP_WeaponInfo FindWeaponInfoForTag(const FGameplayTag& WeaponTag, bool bLogNotFound) const;
};
