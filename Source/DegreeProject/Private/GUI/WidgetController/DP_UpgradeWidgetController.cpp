#include "GUI/WidgetController/DP_UpgradeWidgetController.h"
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

TArray<FUpgradeCardInfo> UDP_UpgradeWidgetController::GetNumberOfUniqueCards(int NumberOfCards, bool bWeaponsOnly) const
{
	TArray<FGameplayAbilitySpecHandle> AbilityHandles;
	AbilitySystemComponentRef->GetAllAbilities(AbilityHandles);

	for (const FGameplayAbilitySpecHandle& AbilityHandle : AbilityHandles)
	{
		FGameplayAbilitySpec* Spec = AbilitySystemComponentRef->FindAbilitySpecFromHandle(AbilityHandle);
		if (Spec && Spec->Ability)
		{
			UGameplayAbility* Ability = Spec->Ability;

			// Option 1: Get tags from the Ability directly
			const FGameplayTagContainer& AbilityTags = Ability->GetAssetTags();

			// Option 2: Get Activation Owned Tags (if that's what you want)
			// const FGameplayTagContainer& ActivationTags = Spec->DynamicAbilityTags;

			// Debug: Print or log the tags
			for (const FGameplayTag& Tag : AbilityTags)
			{
				UE_LOG(LogTemp, Log, TEXT("Ability Tag: %s"), *Tag.ToString());
			}
		}
	}
	
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
