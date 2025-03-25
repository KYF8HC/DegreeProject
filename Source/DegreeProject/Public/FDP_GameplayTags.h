#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

struct FDP_GameplayTags
{
public:
	static const FDP_GameplayTags& Get() { return GameplayTags;}
	static void InitializeNativeGameplayTags();

	FGameplayTag Attributes_Vital_Health;
	FGameplayTag Attributes_Vital_MaxHealth;
	FGameplayTag Attributes_Vital_AbilityResource;
	FGameplayTag Attributes_Vital_MaxAbilityResource;
	
	FGameplayTag Attributes_Primary_Stamina;
	FGameplayTag Attributes_Primary_Armor;
	FGameplayTag Attributes_Primary_MagicResist;
	
	FGameplayTag Attributes_Special_Strength;
	FGameplayTag Attributes_Special_Agility;
	FGameplayTag Attributes_Special_Intellect;
	
	FGameplayTag Attributes_Secondary_AbilityHaste;
	FGameplayTag Attributes_Secondary_Mastery;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_CriticalStrikeChance;
	FGameplayTag Attributes_Secondary_CriticalStrikeDamage;
	FGameplayTag Attributes_Secondary_DodgeChance;

	FGameplayTag Damage;
	FGameplayTag Damage_Magic_Fire;
	FGameplayTag Damage_Magic_Frost;
	FGameplayTag Damage_Magic_Lightning;
	FGameplayTag Damage_Physical;

	FGameplayTag Resistance_Magic_Fire;
	FGameplayTag Resistance_Magic_Frost;
	FGameplayTag Resistance_Magic_Lightning;

	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;

	FGameplayTag Abilities_Attack;
	FGameplayTag Cooldown_Attack;
	
private:
	static FDP_GameplayTags GameplayTags;
	
};
