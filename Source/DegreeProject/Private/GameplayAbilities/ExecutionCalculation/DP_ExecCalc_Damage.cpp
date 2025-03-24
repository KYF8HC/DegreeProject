#include "GameplayAbilities/ExecutionCalculation/DP_ExecCalc_Damage.h"
#include "AbilitySystemComponent.h"
#include "DP_AbilityTypes.h"
#include "FDP_GameplayTags.h"
#include "Data/DP_CharacterClassInfo.h"
#include "GameplayAbilities/DP_AbilitySystemLibrary.h"
#include "Interaction/CombatInterface.h"

UDP_ExecCalc_Damage::UDP_ExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().DodgeChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalStrikeChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalStrikeDamageDef);
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
	float Damage = Spec.GetSetByCallerMagnitude(FDP_GameplayTags::Get().Damage_Physical);

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
	FRealCurve* ArmorPenCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("ArmorPenetrationCoeff"), FString());
	const float ArmorPenCoeff = ArmorPenCurve->Eval(SourceCombatInterface->GetPlayerLevel());
	
	//Armor reduces damage by a percentage
	FRealCurve* EffectiveArmorCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("EffectiveArmorCoeff"), FString());
	const float EffectiveArmorCoeff = EffectiveArmorCurve->Eval(TargetCombatInterface->GetPlayerLevel());
	
	const float EffectiveArmor = TargetArmor * (100 - SourceArmorPen * ArmorPenCoeff) / 100;
	Damage *= (100 - EffectiveArmor * EffectiveArmorCoeff) / 100;

	//Critical Strike increases damage by a percentage
	float CriticalStrikeChance = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalStrikeChanceDef, EvaluateParams, CriticalStrikeChance);

	float CriticalStrikeDamage = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalStrikeDamageDef, EvaluateParams, CriticalStrikeDamage);
	
	const float CriticalStrike = Damage * (1 + CriticalStrikeDamage / 100.0f);
	bool bIsCriticalHit = CriticalStrikeChance / 100.0f > FMath::FRand();

	UDP_AbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, bIsCriticalHit);
	
	Damage = bIsCriticalHit ? CriticalStrike : Damage;
	
	const FGameplayModifierEvaluatedData EvaluatedData(UDP_AttributeSet::GetIncomingDamageAttribute(),
	                                                   EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
