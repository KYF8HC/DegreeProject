#include "GameplayAbilities/ModMagCalc/DP_MMC_MaxHealth.h"
#include "GameplayAbilities/DP_AttributeSet.h"
#include "Interaction/CombatInterface.h"

UDP_MMC_MaxHealth::UDP_MMC_MaxHealth()
{
	StaminaDef.AttributeToCapture = UDP_AttributeSet::GetStaminaAttribute();
	StaminaDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	StaminaDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(StaminaDef);
}

float UDP_MMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = SourceTags;
	EvaluateParams.TargetTags = TargetTags;

	float Stamina = 0.f;
	GetCapturedAttributeMagnitude(StaminaDef, Spec, EvaluateParams, Stamina);
	Stamina = FMath::Max<float>(Stamina, 0.f);

	int32 PlayerLevel = 1;

	if (Spec.GetContext().GetSourceObject()->Implements<UCombatInterface>())
	{
		PlayerLevel = ICombatInterface::Execute_GetCharacterLevel(Spec.GetContext().GetSourceObject());
	}
	return 80.f + 2.5f * Stamina + 10.f * PlayerLevel;
}
