#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

struct FDP_GameplayTags
{
public:
	static const FDP_GameplayTags& Get() { return GameplayTags;}
	static void InitializeNativeGameplayTags();

	FGameplayTag Attributes_Primary_Stamina;
	FGameplayTag Attributes_Primary_Armor;
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Agility;
	FGameplayTag Attributes_Primary_Intellect;
	
	FGameplayTag Attributes_Secondary_Haste;
	FGameplayTag Attributes_Secondary_Mastery;
	FGameplayTag Attributes_Secondary_CriticalStrike;
	FGameplayTag Attributes_Secondary_Versatility;

	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;

	FGameplayTag Damage;
	FGameplayTag Damage_Fire;
	FGameplayTag Damage_Lightning;
	FGameplayTag Damage_Arcane;
	FGameplayTag Damage_Physical;

	FGameplayTag Abilities_Attack;
	FGameplayTag Cooldown_Attack;

	FGameplayTag Effects_HitReact;
	
private:
	static FDP_GameplayTags GameplayTags;
	
};
