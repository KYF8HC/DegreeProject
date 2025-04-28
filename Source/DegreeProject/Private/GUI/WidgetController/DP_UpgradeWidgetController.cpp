#include "GUI/WidgetController/DP_UpgradeWidgetController.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Data/DP_UpgradeCardInfo.h"
#include "GameplayAbilities/DP_AbilitySystemComponent.h"
#include "Interaction/CombatInterface.h"
#include "Interaction/DP_PlayerInterface.h"

void UDP_UpgradeWidgetController::GrantUpgrade(FGuid UniqueIdentifier, EUpgradeCardType CardType)
{
	switch (CardType)
	{
	case EUpgradeCardType::Weapon:
		UpgradeCardInfo->LoadClassByGuidAsync<UGameplayAbility>(
			UniqueIdentifier,
			&FUpgradeCardInfo::AbilityClass,
			[this](const FGameplayTag& AttributeTag, const TSubclassOf<UGameplayAbility>& LoadedAbility, ECardRarity)
			{
				GiveWeaponToPlayerCallback(AttributeTag, LoadedAbility);
			});
		break;
	case EUpgradeCardType::Effect:
		UpgradeCardInfo->LoadClassByGuidAsync<UGameplayEffect>(
			UniqueIdentifier,
			&FUpgradeCardInfo::EffectClass,
			[this](const FGameplayTag& AttributeTag, const TSubclassOf<UGameplayEffect>& LoadedEffect,
			       ECardRarity CardRarity)
			{
				ApplyEffectToPlayerCallback(AttributeTag,  CardRarity, LoadedEffect);
			});
		break;
	default:
		break;
	}
}

TArray<FUpgradeCardInfo> UDP_UpgradeWidgetController::GetNumberOfUniqueCards(int NumberOfCards) const
{
	int32 PlayerLevel = 1;
	FGameplayTagContainer OwnedWeapons;

	if (PlayerCharacterRef->Implements<UCombatInterface>())
	{
		PlayerLevel = ICombatInterface::Execute_GetCharacterLevel(PlayerCharacterRef);
	}

	if (PlayerCharacterRef->Implements<UDP_PlayerInterface>())
	{
		OwnedWeapons = IDP_PlayerInterface::Execute_GetOwnedWeapons(PlayerCharacterRef);
	}

	return UpgradeCardInfo->GetNumberOfUniqueCards(NumberOfCards, PlayerLevel, OwnedWeapons);
}

void UDP_UpgradeWidgetController::GiveWeaponToPlayerCallback(const FGameplayTag& WeaponTag,
                                                             const TSubclassOf<UGameplayAbility>& WeaponClass) const
{
	UDP_AbilitySystemComponent* ASC = Cast<UDP_AbilitySystemComponent>(AbilitySystemComponentRef);
	if (ASC == nullptr) return;
	ASC->GiveWeaponToPlayerByTag(WeaponTag, WeaponClass);
}

void UDP_UpgradeWidgetController::ApplyEffectToPlayerCallback(const FGameplayTag& AttributeTag,
                                                              const ECardRarity CardRarity,
                                                              const TSubclassOf<UGameplayEffect>& EffectClass) const
{
	FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponentRef->MakeEffectContext();
	EffectContextHandle.AddSourceObject(PlayerCharacterRef);
	const FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponentRef->MakeOutgoingSpec(
		EffectClass, 1, EffectContextHandle);

	float Scalar = 0.0f;

	switch (CardRarity)
	{
	case ECardRarity::Common: Scalar = 1.05f;
		break;
	case ECardRarity::Rare: Scalar = 1.1f;
		break;
	case ECardRarity::Epic: Scalar = 1.25f;
		break;
	case ECardRarity::Legendary: Scalar = 1.5f;
		break;
	default: break;
	}

	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(EffectSpecHandle, AttributeTag, Scalar);

	AbilitySystemComponentRef->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}

void UDP_UpgradeWidgetController::InitializeWidgetController()
{
	Super::InitializeWidgetController();
}
