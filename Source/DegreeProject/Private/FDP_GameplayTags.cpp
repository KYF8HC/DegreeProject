#include "FDP_GameplayTags.h"
#include "GameplayTagsManager.h"

FDP_GameplayTags FDP_GameplayTags::GameplayTags;

void FDP_GameplayTags::InitializeNativeGameplayTags()
{
	/*
	 * Primary Attributes
	 */
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Strength"),
		FString("")
		);

	GameplayTags.Attributes_Primary_Stamina = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Stamina"),
		FString("")
		);

	GameplayTags.Attributes_Primary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Armor"),
		FString("Increases Armor")
		);

	GameplayTags.Attributes_Primary_Agility = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Agility"),
		FString("")
		);

	GameplayTags.Attributes_Primary_Intellect = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Intellect"),
		FString("")
		);
	

	/*
	 * Secondary Attributes
	 */
	
	GameplayTags.Attributes_Secondary_Haste = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Haste"),
		FString("")
		);

	GameplayTags.Attributes_Secondary_Mastery = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Mastery"),
		FString("")
		);

	GameplayTags.Attributes_Secondary_CriticalStrike = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalStrike"),
		FString("")
		);

	GameplayTags.Attributes_Secondary_Versatility = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Versatility"),
		FString("")
		);

	/*
	 * Input Tags
	 */
	
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.LMB"),
		FString("Input Tag for Left Mouse Button")
		);

	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.RMB"),
		FString("Input Tag for Right Mouse Button")
		);

	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.1"),
		FString("Input Tag for 1 key")
		);

	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.2"),
		FString("Input Tag for 2 key")
		);

	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.3"),
		FString("Input Tag for 3 key")
		);

	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.4"),
		FString("Input Tag for 4 key")
		);

	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage"),
		FString("Damage")
		);

	/*
	 * Damage Types
	 */

	GameplayTags.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Fire"),
		FString("Fire Damage Type")
		);
	GameplayTags.Damage_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Lightning"),
		FString("Lightning Damage Type")
		);
	GameplayTags.Damage_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Arcane"),
		FString("Arcane Damage Type")
		);
	GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Physical"),
		FString("Physical Damage Type")
		);

	/*
	 * Effects
	 */

	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.HitReact"),
		FString("Tag granted when Hit Reacting")
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
