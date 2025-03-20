#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GameplayAbilities/DP_AttributeSet.h"
#include "DP_ExecCalc_Damage.generated.h"

struct DP_DamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DodgeChance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration)
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalStrikeChance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalStrikeDamage)
	
	DP_DamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDP_AttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDP_AttributeSet, DodgeChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDP_AttributeSet, ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDP_AttributeSet, CriticalStrikeChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDP_AttributeSet, CriticalStrikeDamage, Source, false);
	}
};

static const DP_DamageStatics& DamageStatics()
{
	static DP_DamageStatics DStatics;
	return DStatics;
}

UCLASS()
class DEGREEPROJECT_API UDP_ExecCalc_Damage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UDP_ExecCalc_Damage();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
