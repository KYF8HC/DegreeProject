#include "GameplayAbilities/DP_AttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "Characters/DP_PlayerCharacter.h"
#include "Interaction/CombatInterface.h"

UDP_AttributeSet::UDP_AttributeSet()
{
	
}

void UDP_AttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UDP_AttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDP_AttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDP_AttributeSet, AbilityResource, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDP_AttributeSet, MaxAbilityResource, COND_None, REPNOTIFY_Always);
}

void UDP_AttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{		
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}
	else if (Data.EvaluatedData.Attribute == GetAbilityResourceAttribute())
	{
		SetAbilityResource(FMath::Clamp(GetAbilityResource(), 0.0f, GetMaxAbilityResource()));
	}
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
