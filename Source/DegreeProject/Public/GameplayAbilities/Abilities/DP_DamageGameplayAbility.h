#pragma once

#include "CoreMinimal.h"
#include "DP_GameplayAbility.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "DP_DamageGameplayAbility.generated.h"

class UEnvQuery;
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
	TSubclassOf<UGameplayEffect> DamageEffectClass{};

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes{};
	

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnOutOfAmmo();

	
private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Attributes", meta = (AllowPrivateAccess = "true"))
	bool bShouldSpawnOnActor{true};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Attributes", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEnvQuery> SpawnQuery{};
	
	void InitializeEffectSpecHandle(AActor* NewActor, FGameplayEffectSpecHandle& SpecHandle);
	void SetupAbilityActor(AActor* NewActor, FGameplayEffectSpecHandle SpecHandle);
	void SpawnAbilityActor(const FTransform& SpawnTransform);
	void StartAbilityActorSpawn();
	
	UFUNCTION()
	void OnSpawnQueryFinished(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);
};