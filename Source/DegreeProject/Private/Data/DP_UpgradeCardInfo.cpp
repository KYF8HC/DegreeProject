#include "Data/DP_UpgradeCardInfo.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/AssetManager.h"

FUpgradeCardInfo UDP_UpgradeCardInfo::FindUpgradeCardInfoForTag(const FGameplayTag& WeaponTag, bool bLogNotFound) const
{
	for (const FUpgradeCardInfo& WeaponInfo : UpgradeCardInfoArray)
	{
		if (WeaponInfo.UpgradeTag == WeaponTag)
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

TArray<FUpgradeCardInfo> UDP_UpgradeCardInfo::GetNumberOfUniqueCards(
	const int NumberOfCards, const int PlayerLevel, const FGameplayTagContainer& OwnedWeapons) const
{
	if (UpgradeCardInfoArray.Num() < 3)
	{
		return UpgradeCardInfoArray;
	}

	TArray<FUpgradeCardInfo> ShuffledArray = UpgradeCardInfoArray;
	ShuffledArray.Sort([](const FUpgradeCardInfo&, const FUpgradeCardInfo&)
	{
		return FMath::RandBool();
	});

	TArray<FUpgradeCardInfo> UniqueCards;
	for (const FUpgradeCardInfo& Info : ShuffledArray)
	{
		if (ShouldIncludeCard(Info, PlayerLevel, OwnedWeapons))
		{
			UniqueCards.Add(Info);
			if (UniqueCards.Num() >= NumberOfCards)
				break;
		}
	}

	return UniqueCards;
}

bool UDP_UpgradeCardInfo::ShouldIncludeCard(const FUpgradeCardInfo& Info, int PlayerLevel, const FGameplayTagContainer& OwnedWeapons) const
{
	if (PlayerLevel % 6 == 0 || PlayerLevel == 1)
	{
		if (OwnedWeapons.HasTagExact(Info.UpgradeTag))
			return false;
		
		return Info.UpgradeCardType == EUpgradeCardType::Weapon;
	}

	if (Info.UpgradeCardType != EUpgradeCardType::Weapon)
	{
		if (Info.UpgradeCardType == EUpgradeCardType::WeaponUpgrade && !OwnedWeapons.HasTagExact(Info.UpgradeTag))
				return false;
		
		return CheckRarity(Info);
	}

	return false;
}

bool UDP_UpgradeCardInfo::CheckRarity(const FUpgradeCardInfo& Info) const
{
	static const TMap<ECardRarity, int32> RarityChances = {
		{ ECardRarity::Common,     100 },
		{ ECardRarity::Rare,        50 },
		{ ECardRarity::Epic,        25 },
		{ ECardRarity::Legendary,   10 }
	};

	if (const int32* Chance = RarityChances.Find(Info.CardRarity))
	{
		return FMath::RandRange(0, 100) < *Chance;
	}
    
	return false;
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
