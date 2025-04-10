#include "Data/DP_UpgradeCardInfo.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

FUpgradeCardInfo UDP_UpgradeCardInfo::FindUpgradeCardInfoForTag(const FGameplayTag& WeaponTag, bool bLogNotFound) const
{
	for (const FUpgradeCardInfo& WeaponInfo : UpgradeCardInfoArray)
	{
		if (WeaponInfo.AbilityTag == WeaponTag)
		{
			return WeaponInfo;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("WeaponInfo for tag %s not found"), *WeaponTag.ToString());
	}

	return FUpgradeCardInfo();
}

void UDP_UpgradeCardInfo::LoadWeaponClassByGuidAsync(const FGuid& UniqueIdentifier, TFunction<void(const FGameplayTag&, const TSubclassOf<UGameplayAbility>&)> Callback)
{
	for (const FUpgradeCardInfo& UpgradeCardInfo : UpgradeCardInfoArray)
	{
		if (UpgradeCardInfo.UpgradeCardGuid == UniqueIdentifier)
		{
			TSoftClassPtr<UGameplayAbility> SoftClass = UpgradeCardInfo.AbilityClass;
			FGameplayTag WeaponTag = UpgradeCardInfo.AbilityTag;
			
			CancelAsyncLoading();
			AsyncLoad(SoftClass, [WeaponTag, SoftClass, Callback]()
			{
				const TSubclassOf<UGameplayAbility> LoadedClass = SoftClass.Get();
				Callback(WeaponTag, LoadedClass);
			});
			StartAsyncLoading();

			return;
		}
	}

	// If not found
	Callback(FGameplayTag(), nullptr);
}

void UDP_UpgradeCardInfo::LoadEffectClassByGuidAsync(const FGuid& UniqueIdentifier,
	TFunction<void(const TSubclassOf<UGameplayEffect>&)> Callback)
{
	for (const FUpgradeCardInfo& UpgradeCardInfo : UpgradeCardInfoArray)
	{
		if (UpgradeCardInfo.UpgradeCardGuid == UniqueIdentifier)
		{
			TSoftClassPtr<UGameplayEffect> SoftClass = UpgradeCardInfo.EffectClass;
			
			CancelAsyncLoading();
			AsyncLoad(SoftClass, [ SoftClass, Callback]()
			{
				const TSubclassOf<UGameplayEffect> LoadedClass = SoftClass.Get();
				Callback(LoadedClass);
			});
			StartAsyncLoading();

			return;
		}
	}

	// If not found
	Callback(nullptr);
}

TArray<FUpgradeCardInfo> UDP_UpgradeCardInfo::GetNumberOfUniqueCards(int NumberOfCards) const
{
	TArray<FUpgradeCardInfo> UniqueCards;
	if (UpgradeCardInfoArray.Num() < 3)
	{
		UniqueCards = UpgradeCardInfoArray;
	}
	else
	{
		TArray<FUpgradeCardInfo> ShuffledArray = UpgradeCardInfoArray;
		ShuffledArray.Sort([](const FUpgradeCardInfo&, const FUpgradeCardInfo&) { return FMath::RandBool(); });

		for (int32 i = 0; i < NumberOfCards; ++i)
		{
			UniqueCards.Add(ShuffledArray[i]);
		}
	}
	return UniqueCards;
}

#if WITH_EDITOR

void UDP_UpgradeCardInfo::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	for (FUpgradeCardInfo& Info : UpgradeCardInfoArray)
	{
		if (!Info.UpgradeCardGuid.IsValid())
		{
			Info.UpgradeCardGuid = FGuid::NewGuid();
			UE_LOG(LogTemp, Log, TEXT("Generated new GUID for upgrade card"));
		}
	}
}

#endif