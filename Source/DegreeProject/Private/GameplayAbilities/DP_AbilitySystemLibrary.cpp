#include "GameplayAbilities/DP_AbilitySystemLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "Core/DP_GameMode.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"

void UDP_AbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject,
                                                           ECharacterClass CharacterClass, float Level,
                                                           UAbilitySystemComponent* ASC)
{
	AActor* AvatarActor = ASC->GetAvatarActor();

	UDP_CharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	if (ClassDefaultInfo.PrimaryAttributes)
	{
		FGameplayEffectContextHandle PrimaryAttributesContextHandle = ASC->MakeEffectContext();
		PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
		const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(
			ClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttributesContextHandle);
		ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());
	}

	if (CharacterClassInfo->SecondaryAttributes)
	{
		FGameplayEffectContextHandle SecondaryAttributesContextHandle = ASC->MakeEffectContext();
		SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
		const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(
			CharacterClassInfo->SecondaryAttributes, Level, SecondaryAttributesContextHandle);
		ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());
	}
	
	if (CharacterClassInfo->VitalAttributes)
	{
		FGameplayEffectContextHandle VitalAttributesContextHandle = ASC->MakeEffectContext();
		VitalAttributesContextHandle.AddSourceObject(AvatarActor);
		const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(
			CharacterClassInfo->VitalAttributes, Level, VitalAttributesContextHandle);
		ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
	}
}

void UDP_AbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, ECharacterClass CharacterClass,
                                                    UAbilitySystemComponent* ASC)
{
	UDP_CharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if (CharacterClassInfo == nullptr) return;
	for (TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		ASC->GiveAbility(AbilitySpec);
	}
	const FCharacterClassDefaultInfo DefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	for (TSubclassOf<UGameplayAbility> AbilityClass : DefaultInfo.StartupAbilities)
	{
		ICombatInterface* CombatInterface = Cast<ICombatInterface>(ASC->GetAvatarActor());
		if (CombatInterface)
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, CombatInterface->GetPlayerLevel());
			ASC->GiveAbility(AbilitySpec);
		}
	}
}

UDP_CharacterClassInfo* UDP_AbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	ADP_GameMode* AuraGameMode = Cast<ADP_GameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (AuraGameMode == nullptr) return nullptr;
	return AuraGameMode->CharacterClassInfo;
}
