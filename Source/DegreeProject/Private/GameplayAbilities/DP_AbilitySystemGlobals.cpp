#include "GameplayAbilities/DP_AbilitySystemGlobals.h"

#include "DP_AbilityTypes.h"

FGameplayEffectContext* UDP_AbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FDP_GameplayEffectContext();
}
