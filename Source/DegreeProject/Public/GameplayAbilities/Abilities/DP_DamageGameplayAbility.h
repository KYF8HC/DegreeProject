#pragma once

#include "CoreMinimal.h"
#include "DP_GameplayAbility.h"
#include "DP_DamageGameplayAbility.generated.h"


UCLASS()
class DEGREEPROJECT_API UDP_DamageGameplayAbility : public UDP_GameplayAbility
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void CauseDamage();
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;
};
