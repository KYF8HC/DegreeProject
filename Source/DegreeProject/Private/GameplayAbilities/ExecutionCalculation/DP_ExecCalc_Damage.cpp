#include "GameplayAbilities/ExecutionCalculation/DP_ExecCalc_Damage.h"
#include "AbilitySystemComponent.h"
#include "DP_AbilityTypes.h"
#include "FDP_GameplayTags.h"
#include "Data/DP_CharacterClassInfo.h"
#include "GameplayAbilities/DP_AbilitySystemLibrary.h"
#include "GameplayAbilities/DP_AttributeSet.h"
#include "Interaction/CombatInterface.h"

struct DP_DamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DodgeChance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration)
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalStrikeChance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalStrikeDamage)
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(FrostResistance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance)

	friend static DP_DamageStatics& DamageStatics();
	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition>& GetTagsToCaptureDef()
	{
		if (TagsToCaptureDefs.IsEmpty())
			InitMap();
		return TagsToCaptureDefs;
	}

private:
	DP_DamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDP_AttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDP_AttributeSet, DodgeChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDP_AttributeSet, ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDP_AttributeSet, CriticalStrikeChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDP_AttributeSet, CriticalStrikeDamage, Source, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UDP_AttributeSet, FireResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDP_AttributeSet, FrostResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDP_AttributeSet, LightningResistance, Target, false);	
	}

	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;
	void InitMap()
	{
		const FDP_GameplayTags& Tags = FDP_GameplayTags::Get();
		TagsToCaptureDefs.Add(Tags.Attributes_Primary_Armor, ArmorDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_DodgeChance, DodgeChanceDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_ArmorPenetration, ArmorPenetrationDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalStrikeChance, CriticalStrikeChanceDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalStrikeDamage, CriticalStrikeDamageDef);

		TagsToCaptureDefs.Add(Tags.Resistance_Magic_Fire, FireResistanceDef);
		TagsToCaptureDefs.Add(Tags.Resistance_Magic_Frost, FrostResistanceDef);
		TagsToCaptureDefs.Add(Tags.Resistance_Magic_Lightning, LightningResistanceDef);
	}
};

static DP_DamageStatics& DamageStatics()
{
	static DP_DamageStatics DStatics;
	return DStatics;
}

UDP_ExecCalc_Damage::UDP_ExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().DodgeChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalStrikeChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalStrikeDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().FireResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().FrostResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().LightningResistanceDef);
}

void UDP_ExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                 FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceAvatar);
	ICombatInterface* TargetCombatInterface = Cast<ICombatInterface>(TargetAvatar);

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = SourceTags;
	EvaluateParams.TargetTags = TargetTags;

	//Get Damage Set by Caller Magnitude
	float Damage = 0.0f;
	for (const TTuple<FGameplayTag, FGameplayTag>& Pair : FDP_GameplayTags::Get().DamageTypesToResistances)
	{
		const FGameplayTag DamageTypeTag = Pair.Key;
		const FGameplayTag ResistanceTypeTag = Pair.Value;

		if (DamageTypeTag == FDP_GameplayTags::Get().Damage_Physical)
		{
			Damage += Spec.GetSetByCallerMagnitude(Pair.Key, false, 0.0f);
			continue;
		}

		checkf(DamageStatics().GetTagsToCaptureDef().Contains(ResistanceTypeTag),
		       TEXT("UDP_ExecCalc_Damage::Execute_Implementation: TagsToCaptureDefs does not contain Tag: [%s]"),
		       *ResistanceTypeTag.ToString());
		const FGameplayEffectAttributeCaptureDefinition CaptureDef = DamageStatics().GetTagsToCaptureDef()[ResistanceTypeTag];
		
		float DamageTypeValue = Spec.GetSetByCallerMagnitude(Pair.Key, false, 0.0f);
		
		float ResistanceValue = 0.0f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDef, EvaluateParams, ResistanceValue);
		ResistanceValue = FMath::Clamp(ResistanceValue, 0.0f, 100.0f);
		
		DamageTypeValue *= (100.0f - ResistanceValue) / 100.0f;
		Damage += DamageTypeValue;
	}

	//Capture Dodge Chance on Target
	float DodgeChance = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DodgeChanceDef, EvaluateParams,
	                                                           DodgeChance);
	DodgeChance = FMath::Max<float>(DodgeChance, 0.0f);

	bool bDodgedHit = DodgeChance / 100.0f > FMath::FRand();

	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();
	UDP_AbilitySystemLibrary::SetIsDodgedHit(EffectContextHandle, bDodgedHit);

	//if successful dodge then target receives no damage
	Damage = bDodgedHit ? 0.0f : Damage;

	float TargetArmor = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluateParams, TargetArmor);
	TargetArmor = FMath::Max<float>(TargetArmor, 0.0f);

	float SourceArmorPen = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef, EvaluateParams,
	                                                           SourceArmorPen);
	SourceArmorPen = FMath::Max<float>(SourceArmorPen, 0.0f);

	UDP_CharacterClassInfo* CharacterClassInfo = UDP_AbilitySystemLibrary::GetCharacterClassInfo(SourceAvatar);

	//Armor penetration ignores a percentage of the target's armor
	FRealCurve* ArmorPenCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(
		FName("ArmorPenetrationCoeff"), FString());
	const float ArmorPenCoeff = ArmorPenCurve->Eval(SourceCombatInterface->GetCharacterLevel());

	//Armor reduces damage by a percentage
	FRealCurve* EffectiveArmorCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(
		FName("EffectiveArmorCoeff"), FString());
	const float EffectiveArmorCoeff = EffectiveArmorCurve->Eval(TargetCombatInterface->GetCharacterLevel());

	const float EffectiveArmor = TargetArmor * (100 - SourceArmorPen * ArmorPenCoeff) / 100;
	Damage *= (100 - EffectiveArmor * EffectiveArmorCoeff) / 100;

	//Critical Strike increases damage by a percentage
	float CriticalStrikeChance = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalStrikeChanceDef, EvaluateParams,
	                                                           CriticalStrikeChance);

	float CriticalStrikeDamage = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalStrikeDamageDef, EvaluateParams,
	                                                           CriticalStrikeDamage);

	const float CriticalStrike = Damage * (1 + CriticalStrikeDamage / 100.0f);
	bool bIsCriticalHit = CriticalStrikeChance / 100.0f > FMath::FRand();

	UDP_AbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, bIsCriticalHit);

	Damage = bIsCriticalHit ? CriticalStrike : Damage;
	
	const FGameplayModifierEvaluatedData EvaluatedData(UDP_AttributeSet::GetIncomingDamageAttribute(),
	                                                   EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
