#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/AssetManager.h"
#include "Engine/DataAsset.h"
#include "Engine/StreamableManager.h"
#include "DP_UpgradeCardInfo.generated.h"

class UGameplayEffect;
class UGameplayAbility;
class UTexture2D;

UENUM(BlueprintType)
enum class ECardRarity : uint8
{
	None,
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
	FGameplayTag UpgradeTag{};

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

USTRUCT()
struct FUpgradeCardInfoVital
{
	GENERATED_BODY()

	UPROPERTY()
	FGuid UpgradeCardGuid{};

	UPROPERTY()
	ECardRarity CardRarity{ECardRarity::Common};
};

UCLASS()
class DEGREEPROJECT_API UDP_UpgradeCardInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FUpgradeCardInfo> UpgradeCardInfoArray{};

	FUpgradeCardInfo FindUpgradeCardInfoForTag(const FGameplayTag& WeaponTag, bool bLogNotFound) const;
	//void LoadWeaponClassByGuidAsync(const FGuid& UniqueIdentifier, TFunction<void(const FGameplayTag&, const TSubclassOf<UGameplayAbility>&)> Callback);
	//void LoadEffectClassByGuidAsync(const FGuid& UniqueIdentifier, TFunction<void(const FGameplayTag&, const TSubclassOf<UGameplayEffect>&)> Callback);
	TArray<FUpgradeCardInfo> GetNumberOfUniqueCards(const int NumberOfCards, const int PlayerLevel, const FGameplayTagContainer& OwnedWeapons) const;
	
	// The templated async load function
	template<typename T>
	void LoadClassByGuidAsync(
		const FGuid& UniqueIdentifier,
		TSoftClassPtr<T> FUpgradeCardInfo::* ClassMemberPtr,
		TFunction<void(const FGameplayTag&, const TSubclassOf<T>&, ECardRarity)> Callback);
	
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

private:
	bool ShouldIncludeCard(const FUpgradeCardInfo& Info, int PlayerLevel, const FGameplayTagContainer& OwnedWeapons) const;
	bool CheckRarity(const FUpgradeCardInfo& Info) const;
};

template <typename T>
void UDP_UpgradeCardInfo::LoadClassByGuidAsync(const FGuid& UniqueIdentifier,
	TSoftClassPtr<T> FUpgradeCardInfo::* ClassMemberPtr,
	TFunction<void(const FGameplayTag&, const TSubclassOf<T>&, ECardRarity)> Callback)
{
	for (const FUpgradeCardInfo& UpgradeCardInfo : UpgradeCardInfoArray)
	{
		if (UpgradeCardInfo.UpgradeCardGuid == UniqueIdentifier)
		{
			FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
			TSoftClassPtr<T> SoftClass = UpgradeCardInfo.*ClassMemberPtr;
			FGameplayTag Tag = UpgradeCardInfo.UpgradeTag;
			ECardRarity Rarity = UpgradeCardInfo.CardRarity; 

			Streamable.RequestAsyncLoad(SoftClass.ToSoftObjectPath(), [Tag, Rarity, SoftClass, Callback]()
			{
				const TSubclassOf<T> LoadedClass = SoftClass.Get();
				Callback(Tag, LoadedClass, Rarity);
			});

			return;
		}
	}

	// If not found
	Callback(FGameplayTag(), nullptr, ECardRarity::None);
}