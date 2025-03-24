#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "DP_AbilitySystemGlobals.generated.h"

UCLASS()
class DEGREEPROJECT_API UDP_AbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()

	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};
