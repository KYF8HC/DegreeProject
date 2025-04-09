#include "GUI/WidgetController/DP_UpgradeWidgetController.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Data/DP_UpgradeCardInfo.h"
#include "GameplayAbilities/DP_AbilitySystemComponent.h"


void UDP_UpgradeWidgetController::GivePlayerWeaponByTag(const FGameplayTag& InWeaponTag)
{
	UpgradeCardInfo->FindAbilityClassByTagAsync(InWeaponTag,
	                                       [this](const FGameplayTag& WeaponTag, const TSubclassOf<UGameplayAbility>& LoadedAbility)
	                                       {
		                                       GivePlayerWeaponInternal(WeaponTag, LoadedAbility);
	                                       });
}

void UDP_UpgradeWidgetController::ApplyEffectToPlayer(const FGuid& UniqueIdentifier) const
{
	UpgradeCardInfo->FindEffectClassByUniqueIdentifierAsync(UniqueIdentifier,
															[this](const TSubclassOf<UGameplayEffect>& LoadedEffect)
															{
																ApplyEffectToPlayerInternal(LoadedEffect);
															});
}

void UDP_UpgradeWidgetController::GivePlayerWeaponInternal(const FGameplayTag& WeaponTag,
                                                           const TSubclassOf<UGameplayAbility>& WeaponClass) const
{
	UDP_AbilitySystemComponent* ASC = Cast<UDP_AbilitySystemComponent>(AbilitySystemComponentRef);
	if (ASC == nullptr) return;
	ASC->GivePlayerWeapon(WeaponTag, WeaponClass);
}

void UDP_UpgradeWidgetController::ApplyEffectToPlayerInternal(const TSubclassOf<UGameplayEffect>& EffectClass) const
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