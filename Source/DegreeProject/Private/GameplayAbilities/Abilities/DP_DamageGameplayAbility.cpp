#include "GameplayAbilities/Abilities/DP_DamageGameplayAbility.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilities/DP_AbilitySystemComponent.h"

void UDP_DamageGameplayAbility::CauseDamage()
{
	FGameplayEffectSpecHandle DamageSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass, 1.0f);
	for (TTuple<FGameplayTag, FScalableFloat> Pair : DamageTypes)
	{
		const float ScaleDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageSpecHandle, Pair.Key, ScaleDamage);
	}

	//TODO: Not flexible enough, should receive a target actor as a parameter
	UDP_AbilitySystemComponent* AbilitySystemComponent = Cast<UDP_AbilitySystemComponent>(
		GetAbilitySystemComponentFromActorInfo());
	
	AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(
		*DamageSpecHandle.Data.Get(),
		UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(AbilitySystemComponent->TargetActorRef));
}
