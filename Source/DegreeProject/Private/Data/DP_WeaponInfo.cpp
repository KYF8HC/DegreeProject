#include "Data/DP_WeaponInfo.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

FWeaponInfo UDP_WeaponInfo::FindWeaponInfoForTag(const FGameplayTag& WeaponTag, bool bLogNotFound) const
{
	for (const FWeaponInfo& WeaponInfo : WeaponInfoArray)
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

	return FWeaponInfo();
}

void UDP_WeaponInfo::FindAbilityClassByTagAsync(const FGameplayTag& WeaponTag, TFunction<void(const FGameplayTag&, const TSubclassOf<UGameplayAbility>&)> Callback)
{
	for (const FWeaponInfo& WeaponInfo : WeaponInfoArray)
	{
		if (WeaponInfo.AbilityTag == WeaponTag)
		{
			FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
			TSoftClassPtr<UGameplayAbility> SoftClass = WeaponInfo.AbilityClass;

			/* TODO: LOOK INTO ASYNCMIXIN
			* CancelAsyncLoading();			// Some objects get reused like in lists, so it's important to cancel anything you had pending doesn't complete.
			* AsyncLoad(ItemOne, CallbackOne);
			* AsyncLoad(ItemTwo, CallbackTwo);
			* StartAsyncLoading();
			*/
			
			Streamable.RequestAsyncLoad(SoftClass.ToSoftObjectPath(), [WeaponTag, SoftClass, Callback]()
			{
				const TSubclassOf<UGameplayAbility> LoadedClass = SoftClass.Get();
				Callback(WeaponTag, LoadedClass);
			});

			return;
		}
	}

	// If not found
	Callback(WeaponTag, nullptr);
}