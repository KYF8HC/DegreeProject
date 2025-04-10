﻿#include "GUI/WidgetController/DP_UpgradeWidgetController.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Data/DP_UpgradeCardInfo.h"
#include "GameplayAbilities/DP_AbilitySystemComponent.h"

void UDP_UpgradeWidgetController::GrantUpgrade(FGuid UniqueIdentifier, EUpgradeCardType CardType)
{
	switch (CardType)
	{
	case EUpgradeCardType::Weapon:
		UpgradeCardInfo->LoadWeaponClassByGuidAsync(UniqueIdentifier,
												[this](const FGameplayTag& WeaponTag,
													   const TSubclassOf<UGameplayAbility>& LoadedAbility)
												{
													GiveWeaponToPlayerCallback(WeaponTag, LoadedAbility);
												});
		break;
	case EUpgradeCardType::Effect:
		UpgradeCardInfo->LoadEffectClassByGuidAsync(UniqueIdentifier,
												[this](const TSubclassOf<UGameplayEffect>& LoadedEffect)
												{
													ApplyEffectToPlayerCallback(LoadedEffect);
												});
		break;
	default:
		break;
	}
}

TArray<FUpgradeCardInfo> UDP_UpgradeWidgetController::GetNumberOfUniqueCards(int NumberOfCards) const
{
	return UpgradeCardInfo->GetNumberOfUniqueCards(NumberOfCards);
}

void UDP_UpgradeWidgetController::GiveWeaponToPlayerCallback(const FGameplayTag& WeaponTag,
                                                             const TSubclassOf<UGameplayAbility>& WeaponClass) const
{
	UDP_AbilitySystemComponent* ASC = Cast<UDP_AbilitySystemComponent>(AbilitySystemComponentRef);
	if (ASC == nullptr) return;
	ASC->GiveWeaponToPlayerByTag(WeaponTag, WeaponClass);
}

void UDP_UpgradeWidgetController::ApplyEffectToPlayerCallback(const TSubclassOf<UGameplayEffect>& EffectClass) const
{
	const FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponentRef->MakeEffectContext();
	const FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponentRef->MakeOutgoingSpec(
		EffectClass, 1, EffectContextHandle);

	AbilitySystemComponentRef->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}

void UDP_UpgradeWidgetController::InitializeWidgetController()
{
	Super::InitializeWidgetController();
}
