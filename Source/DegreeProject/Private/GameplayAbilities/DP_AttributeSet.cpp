#include "GameplayAbilities/DP_AttributeSet.h"
#include "Net/UnrealNetwork.h"

UDP_AttributeSet::UDP_AttributeSet()
{
	InitHealth(50.0f);
	InitMaxHealth(100.0f);
	InitAbilityResource(50.0f);
	InitMaxAbilityResource(100.0f);
}

void UDP_AttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UDP_AttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDP_AttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDP_AttributeSet, AbilityResource, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDP_AttributeSet, MaxAbilityResource, COND_None, REPNOTIFY_Always);
}

void UDP_AttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDP_AttributeSet, Health, OldHealth);
}

void UDP_AttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDP_AttributeSet, MaxHealth, OldMaxHealth);
}

void UDP_AttributeSet::OnRep_AbilityResource(const FGameplayAttributeData& OldAbilityResource)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDP_AttributeSet, AbilityResource, OldAbilityResource);
}

void UDP_AttributeSet::OnRep_MaxAbilityResource(const FGameplayAttributeData& OldMaxAbilityResource)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDP_AttributeSet, MaxAbilityResource, OldMaxAbilityResource);
}
