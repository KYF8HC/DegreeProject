#include "GameplayAbilities/DP_AttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"

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
	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float LocalIncomingDamage = GetIncomingDamage();
		SetIncomingDamage(0.0f);
		if (LocalIncomingDamage > 0.0f)
		{
			const float NewHealth = GetHealth() - LocalIncomingDamage;
			SetHealth(FMath::Clamp(NewHealth, 0.0f, GetMaxHealth()));
			const bool bFatal = NewHealth <= 0.0f;
		}
	}
}

#pragma region OnRep Functions
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

void UDP_AttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDP_AttributeSet, Stamina, OldStamina);
}

void UDP_AttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDP_AttributeSet, Armor, OldArmor);
}

void UDP_AttributeSet::OnRep_MagicResist(const FGameplayAttributeData& OldMagicResist)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDP_AttributeSet, MagicResist, OldMagicResist);
}

void UDP_AttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDP_AttributeSet, Strength, OldStrength);
}

void UDP_AttributeSet::OnRep_Agility(const FGameplayAttributeData& OldAgility)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDP_AttributeSet, Agility, OldAgility);
}

void UDP_AttributeSet::OnRep_Intellect(const FGameplayAttributeData& OldIntellect)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDP_AttributeSet, Intellect, OldIntellect);
}

void UDP_AttributeSet::OnRep_AbilityHaste(const FGameplayAttributeData& OldAbilityHaste)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDP_AttributeSet, AbilityHaste, OldAbilityHaste);
}

void UDP_AttributeSet::OnRep_Mastery(const FGameplayAttributeData& OldMastery)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDP_AttributeSet, Mastery, OldMastery);
}

void UDP_AttributeSet::OnRep_CriticalStrike(const FGameplayAttributeData& OldCriticalStrike)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDP_AttributeSet, CriticalStrike, OldCriticalStrike);
}

void UDP_AttributeSet::OnRep_DodgeChance(const FGameplayAttributeData& OldDodgeChance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDP_AttributeSet, DodgeChance, OldDodgeChance);
}
#pragma endregion