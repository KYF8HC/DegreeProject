#include "FDP_GameplayTags.h"
#include "GameplayTagsManager.h"

FDP_GameplayTags FDP_GameplayTags::GameplayTags;

void FDP_GameplayTags::InitializeNativeGameplayTags()
{
	/*
	 * Primary Attributes
	 */
	
	GameplayTags.Attributes_Primary_Stamina = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Stamina"),
		FString("Increases Health")
		);

	GameplayTags.Attributes_Primary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Armor"),
		FString("Increases Armor")
		);

	/*
	 * Class Specific Attributes
	 */
	
	GameplayTags.Attributes_Special_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Special.Strength"),
		FString("")
		);

	GameplayTags.Attributes_Special_Agility = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Special.Agility"),
		FString("Increases Dodge Chance, Reload Speed, and Movement Speed")
		);

	GameplayTags.Attributes_Special_Intellect = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Special.Intellect"),
		FString("Increases Magic Damage")
		);
	

	/*
	 * Secondary Attributes
	 */
	
	GameplayTags.Attributes_Secondary_AbilityHaste = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.AbilityHaste"),
		FString("Decreases the cooldown of your classes special ability")
		);

	GameplayTags.Attributes_Secondary_Mastery = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Mastery"),
		FString("Increases the effectiveness of your class ability")
		);

	GameplayTags.Attributes_Secondary_CriticalStrike = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalStrike"),
		FString("Increases Critical Strike Chance")
		);

	GameplayTags.Attributes_Secondary_DodgeChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.DodgeChance"),
		FString("Increases Dodge Chance")
		);
	

	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage"),
		FString("Damage")
		);

	/*
	 * Damage Types
	 */

	GameplayTags.Damage_Magic_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Magic.Fire"),
		FString("Fire Damage Type")
		);
	GameplayTags.Damage_Magic_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Magic.Lightning"),
		FString("Lightning Damage Type")
		);
	GameplayTags.Damage_Magic_Frost = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Magic.Frost"),
		FString("Frost Damage Type")
		);
	GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Physical"),
		FString("Physical Damage Type")
		);

	/*
	 * Abilities
	 */

	GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Attack"),
		FString("Attack Ability Tag")
		);

	GameplayTags.Cooldown_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Cooldown.Attack"),
		FString("Cooldown Tag for Attack Ability")
		);
}
