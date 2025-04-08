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

void UDP_UpgradeCardInfo::FindAbilityClassByTagAsync(const FGameplayTag& WeaponTag, TFunction<void(const FGameplayTag&, const TSubclassOf<UGameplayAbility>&)> Callback)
{
	for (const FUpgradeCardInfo& UpgradeCardInfo : UpgradeCardInfoArray)
	{
		if (UpgradeCardInfo.AbilityTag == WeaponTag)
		{
			TSoftClassPtr<UGameplayAbility> SoftClass = UpgradeCardInfo.AbilityClass;
			
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
	Callback(WeaponTag, nullptr);
}

void UDP_UpgradeCardInfo::FindEffectClassByUniqueIdentifierAsync(const FGuid& UniqueIdentifier,
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