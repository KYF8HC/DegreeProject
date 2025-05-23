﻿#include "GameplayAbilities/DP_AbilitySystemLibrary.h"
#include "AbilitySystemComponent.h"
#include "DP_AbilityTypes.h"
#include "GameplayAbilitySpec.h"
#include "Core/DP_GameMode.h"
#include "GameplayAbilities/DP_AbilitySystemComponent.h"
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

	if (ClassDefaultInfo.SecondaryAttributes)
	{
		FGameplayEffectContextHandle SecondaryAttributesContextHandle = ASC->MakeEffectContext();
		SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
		const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(
			ClassDefaultInfo.SecondaryAttributes, Level, SecondaryAttributesContextHandle);
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
	const FCharacterClassDefaultInfo& DefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	for (const FStartupAbilityInfo& StartupAbilityInfo : DefaultInfo.StartupAbilities)
	{
		if (ASC->GetAvatarActor()->Implements<UCombatInterface>())
		{
			if (StartupAbilityInfo.bShouldAutoActivate)
			{
				FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(StartupAbilityInfo.AbilityClass, 1);
				ASC->GiveAbilityAndActivateOnce(AbilitySpec);
			}
			else
			{
				FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(StartupAbilityInfo.AbilityClass,
				                                                        ICombatInterface::Execute_GetCharacterLevel(
					                                                        ASC->GetAvatarActor()));

				ASC->GiveAbility(AbilitySpec);
			}
		}
	}
}


int32 UDP_AbilitySystemLibrary::GetExperienceRewardForClassAndLevel(const UObject* WorldContextObject,
                                                                    ECharacterClass CharacterClass, int32 Level)
{
	UDP_CharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if (CharacterClassInfo == nullptr) return 0;

	const FCharacterClassDefaultInfo Info = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	const float Reward = Info.ExperienceReward.GetValueAtLevel(Level);

	return static_cast<int32>(Reward);
}


UDP_CharacterClassInfo* UDP_AbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	ADP_GameMode* DP_GameMode = Cast<ADP_GameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (DP_GameMode == nullptr) return nullptr;
	return DP_GameMode->CharacterClassInfo;
}

bool UDP_AbilitySystemLibrary::IsDodgedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FDP_GameplayEffectContext* DP_EffectContext = static_cast<const FDP_GameplayEffectContext*>(
		EffectContextHandle.Get()))
		return DP_EffectContext->IsDodgedHit();
	return false;
}

bool UDP_AbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FDP_GameplayEffectContext* DP_EffectContext = static_cast<const FDP_GameplayEffectContext*>(
		EffectContextHandle.Get()))
		return DP_EffectContext->IsCriticalHit();
	return false;
}

void UDP_AbilitySystemLibrary::SetIsDodgedHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsDodgedHit)
{
	if (FDP_GameplayEffectContext* DP_EffectContext = static_cast<FDP_GameplayEffectContext*>(EffectContextHandle.
		Get()))
	{
		DP_EffectContext->SetIsDodgedHit(bInIsDodgedHit);
	}
}

void UDP_AbilitySystemLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle,
                                                bool bInIsCriticalHit)
{
	if (FDP_GameplayEffectContext* DP_EffectContext = static_cast<FDP_GameplayEffectContext*>(EffectContextHandle.
		Get()))
	{
		DP_EffectContext->SetIsCriticalHit(bInIsCriticalHit);
	}
}
