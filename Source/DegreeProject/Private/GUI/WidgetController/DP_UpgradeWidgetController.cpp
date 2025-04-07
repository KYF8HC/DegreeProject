#include "GUI/WidgetController/DP_UpgradeWidgetController.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Data/DP_WeaponInfo.h"
#include "GameplayAbilities/DP_AbilitySystemComponent.h"


void UDP_UpgradeWidgetController::GivePlayerWeaponByTag(const FGameplayTag& InWeaponTag)
{
	WeaponInfo->FindAbilityClassByTagAsync(InWeaponTag,
	                                       [this](const FGameplayTag& WeaponTag, const TSubclassOf<UGameplayAbility>& LoadedAbility)
	                                       {
		                                       GivePlayerWeaponInternal(WeaponTag, LoadedAbility);
	                                       });
}

void UDP_UpgradeWidgetController::GivePlayerWeaponInternal(const FGameplayTag& WeaponTag,
	const TSubclassOf<UGameplayAbility>& WeaponClass) const
{
	UDP_AbilitySystemComponent* ASC = Cast<UDP_AbilitySystemComponent>(AbilitySystemComponentRef);
	if (ASC == nullptr) return;
	ASC->GivePlayerWeapon(WeaponTag, WeaponClass);
}

void UDP_UpgradeWidgetController::InitializeWidgetController()
{
	Super::InitializeWidgetController();
}