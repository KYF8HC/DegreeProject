#include "GameplayAbilities/DP_AttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "FDP_GameplayTags.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "GameplayAbilities/DP_AbilitySystemLibrary.h"
#include "Interaction/CombatInterface.h"
#include "Interaction/DP_PlayerInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Player/DP_PlayerController.h"

UDP_AttributeSet::UDP_AttributeSet()
{
}

void UDP_AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UDP_AttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDP_AttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDP_AttributeSet, AbilityResource, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDP_AttributeSet, MaxAbilityResource, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDP_AttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDP_AttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDP_AttributeSet, MagicResist, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDP_AttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDP_AttributeSet, Agility, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDP_AttributeSet, Intellect, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDP_AttributeSet, AbilityHaste, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDP_AttributeSet, Mastery, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDP_AttributeSet, CriticalStrikeChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDP_AttributeSet, DodgeChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDP_AttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDP_AttributeSet, FireResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDP_AttributeSet, FrostResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDP_AttributeSet, LightningResistance, COND_None, REPNOTIFY_Always);
}

void UDP_AttributeSet::ShowFloatingText(FEffectProperties Props, const float LocalIncomingDamage, bool bInIsDodgedHit,
                                        bool bInIsCriticalHit) const
{
	if (Props.SourceCharacter != Props.TargetCharacter)
	{
		if (ADP_PlayerController* PC = Cast<ADP_PlayerController>((Props.SourceCharacter->Controller)))
		{
			PC->ShowDamageNumber(LocalIncomingDamage, Props.TargetCharacter, bInIsDodgedHit, bInIsCriticalHit);
			return;
		}
		if (ADP_PlayerController* PC = Cast<ADP_PlayerController>((Props.TargetCharacter->Controller)))
		{
			PC->ShowDamageNumber(LocalIncomingDamage, Props.TargetCharacter, bInIsDodgedHit, bInIsCriticalHit);
		}
	}
}

void UDP_AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

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
			if (bFatal)
			{
				ICombatInterface* CombatInterface = Cast<ICombatInterface>(Props.TargetAvatarActor);
				if (CombatInterface)
				{
					CombatInterface->Death();
				}
				SendExperienceEvent(Props);
			}
		}

		const bool bIsDodgedHit = UDP_AbilitySystemLibrary::IsDodgedHit(Props.EffectContextHandle);
		const bool bIsCriticalHit = UDP_AbilitySystemLibrary::IsCriticalHit(Props.EffectContextHandle);
		ShowFloatingText(Props, LocalIncomingDamage, bIsDodgedHit, bIsCriticalHit);
	}

	if (Data.EvaluatedData.Attribute == GetIncomingExperienceAttribute())
	{
		const float LocalIncomingExperience = GetIncomingExperience();
		SetIncomingExperience(0.0f);

		if (Props.SourceCharacter->Implements<UDP_PlayerInterface>())
			IDP_PlayerInterface::Execute_AddToPlayerExperience(Props.SourceCharacter, LocalIncomingExperience);
	}
}


void UDP_AttributeSet::SendExperienceEvent(const FEffectProperties& Props)
{
	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(Props.TargetCharacter))
	{
		const int32 TargetLevel = CombatInterface->GetCharacterLevel();
		const ECharacterClass CharacterClass = ICombatInterface::Execute_GetCharacterClass(Props.TargetCharacter);
		const int32 ExperienceReward = UDP_AbilitySystemLibrary::GetExperienceRewardForClassAndLevel(
			Props.TargetCharacter, CharacterClass, TargetLevel);

		const FDP_GameplayTags GameplayTags = FDP_GameplayTags::Get();
		FGameplayEventData Payload;
		Payload.EventTag = GameplayTags.Attributes_Meta_IncomingExperience;
		Payload.EventMagnitude = ExperienceReward;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Props.SourceCharacter,
		                                                         GameplayTags.Attributes_Meta_IncomingExperience,
		                                                         Payload);
	}
}

void UDP_AttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	// Source = causer of the effect, Target = target of the effect (owner of this AS)

	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->
		AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
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

void UDP_AttributeSet::OnRep_CriticalStrikeChance(const FGameplayAttributeData& OldCriticalStrikeChance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDP_AttributeSet, CriticalStrikeChance, OldCriticalStrikeChance);
}

void UDP_AttributeSet::OnRep_CriticalStrikeDamage(const FGameplayAttributeData& OldCriticalStrikeDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDP_AttributeSet, CriticalStrikeDamage, OldCriticalStrikeDamage);
}

void UDP_AttributeSet::OnRep_DodgeChance(const FGameplayAttributeData& OldDodgeChance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDP_AttributeSet, DodgeChance, OldDodgeChance);
}

void UDP_AttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDP_AttributeSet, ArmorPenetration, OldArmorPenetration);
}

void UDP_AttributeSet::OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDP_AttributeSet, FireResistance, OldFireResistance);
}

void UDP_AttributeSet::OnRep_FrostResistance(const FGameplayAttributeData& OldFrostResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDP_AttributeSet, FrostResistance, OldFrostResistance);
}

void UDP_AttributeSet::OnRep_LightningResistance(const FGameplayAttributeData& OldLightningResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDP_AttributeSet, LightningResistance, OldLightningResistance);
}
#pragma endregion
