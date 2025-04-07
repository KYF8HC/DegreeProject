#include "FDP_GameplayTags.h"

#include "AIController.h"
#include "GameplayTagsManager.h"

FDP_GameplayTags FDP_GameplayTags::GameplayTags;

void FDP_GameplayTags::InitializeNativeGameplayTags()
{
	/*
	 * Primary Attributes
	 */

	GameplayTags.Attributes_Primary_Stamina = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Stamina"),
		FString("Increases Health"));

	GameplayTags.Attributes_Primary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Armor"),
		FString("Increases Armor"));

	/*
	 * Class Specific Attributes
	 */

	GameplayTags.Attributes_Special_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Special.Strength"),
		FString(""));

	GameplayTags.Attributes_Special_Agility = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Special.Agility"),
		FString("Increases Dodge Chance, Reload Speed, and Movement Speed"));

	GameplayTags.Attributes_Special_Intellect = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Special.Intellect"),
		FString("Increases Magic Damage"));


	/*
	 * Secondary Attributes
	 */

	GameplayTags.Attributes_Secondary_AbilityHaste = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.AbilityHaste"),
		FString("Decreases the cooldown of your classes special ability"));

	GameplayTags.Attributes_Secondary_Mastery = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Mastery"),
		FString("Increases the effectiveness of your class ability"));

	GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ArmorPenetration"),
		FString("Ignores a percentage of the target's armor"));

	GameplayTags.Attributes_Secondary_CriticalStrikeChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalStrike"),
		FString("Increases Critical Strike Chance"));

	GameplayTags.Attributes_Secondary_CriticalStrikeDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalStrikeDamage"),
		FString("Increases Critical Strike Damage"));

	GameplayTags.Attributes_Secondary_DodgeChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.DodgeChance"),
		FString("Increases Dodge Chance"));

	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage"),
		FString("Damage"));

	/*
	 * Damage Types
	 */
	GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Physical"),
		FString("Physical Damage Type"));

	GameplayTags.Damage_Magic_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Magic.Fire"),
		FString("Fire Damage Type"));

	GameplayTags.Damage_Magic_Frost = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Magic.Frost"),
		FString("Frost Damage Type"));

	GameplayTags.Damage_Magic_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Magic.Lightning"),
		FString("Lightning Damage Type"));

	/*
	 * Resistance Types
	 */
	GameplayTags.Resistance_Magic_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Resistance.Magic.Fire"),
		FString("Fire Resistance"));

	GameplayTags.Resistance_Magic_Frost = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Resistance.Magic.Frost"),
		FString("Frost Resistance"));

	GameplayTags.Resistance_Magic_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Resistance.Magic.Lightning"),
		FString("Lightning Resistance"));

	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Magic_Fire, GameplayTags.Resistance_Magic_Fire);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Magic_Frost, GameplayTags.Resistance_Magic_Frost);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Magic_Lightning,
	                                          GameplayTags.Resistance_Magic_Lightning);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Physical);

	/*
	 * Abilities
	 */

	GameplayTags.Abilities_Enemy_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Enemy.Attack"),
		FString("Enemy Attack Ability Tag")
	);

	GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Attack"),
		FString("Attack Ability Tag")
	);

	GameplayTags.Abilities_FlameThrower = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.FlameThrower"),
		FString("Flame Thrower Ability Tag")
	);

	GameplayTags.Abilities_Shoot = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Shoot"),
		FString("Shoot Ability Tag")
	);

	GameplayTags.Abilities_LightningRod = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.LightningRod"),
		FString("Lightning Rod Ability Tag")
	);

	/*
	 * Cooldowns
	 */

	GameplayTags.Cooldown_Enemy_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Cooldown.Enemy.Attack"),
		FString("Cooldown Tag for Enemy Attack Ability")
	);

	GameplayTags.Cooldown_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Cooldown.Attack"),
		FString("Cooldown Tag for Attack Ability")
	);

	GameplayTags.Cooldown_FlameThrower = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Cooldown.FlameThrower"),
		FString("Cooldown Tag for Flame Thrower Ability")
	);

	GameplayTags.Cooldown_Shoot = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Cooldown.Shoot"),
		FString("Cooldown Tag for Shoot Ability")
	);

	GameplayTags.Cooldown_LightningRod = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Cooldown.LightningRod"),
		FString("Cooldown Tag for Lightning Rod Ability")
	);

	GameplayTags.CooldownsToAbilities.Add(GameplayTags.Cooldown_Shoot, GameplayTags.Abilities_Shoot);
	GameplayTags.CooldownsToAbilities.Add(GameplayTags.Cooldown_Attack, GameplayTags.Abilities_Attack);
	GameplayTags.CooldownsToAbilities.Add(GameplayTags.Cooldown_FlameThrower, GameplayTags.Abilities_FlameThrower);
	GameplayTags.CooldownsToAbilities.Add(GameplayTags.Cooldown_LightningRod, GameplayTags.Abilities_LightningRod);
}
