#include "GameplayAbilities/DP_AbilitySystemComponent.h"
#include "FDP_GameplayTags.h"

void UDP_AbilitySystemComponent::GiveWeaponToPlayerByTag(const FGameplayTag& WeaponTag,
                                                  const TSubclassOf<UGameplayAbility>& LoadedAbility)
{
	GiveWeaponPlayByTagInternal(LoadedAbility);
	BindAbilityCooldown(WeaponTag);
}

void UDP_AbilitySystemComponent::GiveWeaponPlayByTagInternal(const TSubclassOf<UGameplayAbility>& AbilityClass)
{
	if (AbilityClass)
	{
		const FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		const FGameplayAbilitySpecHandle AbilitySpecHandle = GiveAbility(AbilitySpec);
		TryActivateAbility(AbilitySpecHandle);
	}
}

void UDP_AbilitySystemComponent::BindAbilityCooldown(const FGameplayTag& WeaponTag)
{
	for (const TTuple<FGameplayTag, FGameplayTag>& Pair : FDP_GameplayTags::Get().CooldownsToAbilities)
	{
		const FGameplayTag LocalCooldownTag = Pair.Key;
		const FGameplayTag LocalWeaponTag = Pair.Value;


		if (WeaponTag == LocalWeaponTag)
		{
			RegisterGameplayTagEvent(LocalCooldownTag, EGameplayTagEventType::NewOrRemoved)
				.AddUObject(this, &UDP_AbilitySystemComponent::HandleCooldownTagChanged);
		}
	}
}

void UDP_AbilitySystemComponent::HandleCooldownTagChanged(FGameplayTag GameplayTag, int Count)
{
	if (Count > 0)
		return;
	
	for (const TTuple<FGameplayTag, FGameplayTag>& Pair : FDP_GameplayTags::Get().CooldownsToAbilities)
	{
		const FGameplayTag LocalCooldownTag = Pair.Key;
		const FGameplayTag LocalAbilityTag = Pair.Value;

		if (GameplayTag == LocalCooldownTag)
		{
			FGameplayTagContainer TagContainer;
			TagContainer.AddTag(LocalAbilityTag);
			TryActivateAbilitiesByTag(TagContainer);
		}
	}
}
