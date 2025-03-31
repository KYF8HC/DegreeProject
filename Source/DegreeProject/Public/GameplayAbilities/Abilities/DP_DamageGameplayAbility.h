#pragma once

#include "CoreMinimal.h"
#include "DP_GameplayAbility.h"
#include "DP_DamageGameplayAbility.generated.h"

class ADP_AbilityActor;

UCLASS()
class DEGREEPROJECT_API UDP_DamageGameplayAbility : public UDP_GameplayAbility
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* CombatTarget);
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Attributes", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> AbilityActorClass{};

	UPROPERTY(EditDefaultsOnly, Category = "Ability Attributes")
	float MaxAmmo{10.0f};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnOutOfAmmo();
};