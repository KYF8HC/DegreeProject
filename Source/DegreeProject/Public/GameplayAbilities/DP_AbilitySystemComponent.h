#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "DP_AbilitySystemComponent.generated.h"

class UDP_UpgradeCardInfo;

UCLASS()
class DEGREEPROJECT_API UDP_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Ability System")
	TObjectPtr<AActor> TargetActorRef{};

	void GiveWeaponToPlayerByTag(const FGameplayTag& WeaponTag, const TSubclassOf<UGameplayAbility>& LoadedAbility);

protected:
	void GiveWeaponPlayByTagInternal(const TSubclassOf<UGameplayAbility>& AbilityClass);
	void BindAbilityCooldown(const FGameplayTag& WeaponTag);
	
	UFUNCTION()
	void HandleCooldownTagChanged(FGameplayTag GameplayTag, int Count);
};
