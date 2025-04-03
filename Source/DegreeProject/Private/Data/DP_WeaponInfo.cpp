#include "Data/DP_WeaponInfo.h"

FDP_WeaponInfo UDP_WeaponInfo::FindWeaponInfoForTag(const FGameplayTag& WeaponTag, bool bLogNotFound) const
{
	for (const FDP_WeaponInfo& WeaponInfo : WeaponInfoArray)
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

	return FDP_WeaponInfo();
}
