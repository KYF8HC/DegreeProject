#pragma once

#include "GameplayEffectTypes.h"
#include "DP_AbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FDP_GameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:
	bool IsCriticalHit() const { return bIsCriticalHit; }
	bool IsDodgedHit() const { return bIsDodgedHit; }
	void SetIsCriticalHit(bool bInIsCriticalHit) { bIsCriticalHit = bInIsCriticalHit; }
	void SetIsDodgedHit(bool bInIsDodgedHit) { bIsDodgedHit = bInIsDodgedHit; }

	/** Returns the actual struct used for serialization, subclasses must override this! */
	virtual UScriptStruct* GetScriptStruct() const { return FGameplayEffectContext::StaticStruct(); }
	/** Custom serialization, subclasses must override this */
	virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;

protected:
	UPROPERTY()
	bool bIsDodgedHit = false;

	UPROPERTY()
	bool bIsCriticalHit = false;
};
