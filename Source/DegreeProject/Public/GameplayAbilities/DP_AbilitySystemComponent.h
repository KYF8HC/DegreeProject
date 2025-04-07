#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "DP_AbilitySystemComponent.generated.h"

class UDP_WeaponInfo;

UCLASS()
class DEGREEPROJECT_API UDP_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Ability System")
	TObjectPtr<AActor> TargetActorRef{};

	void GivePlayerWeapon(const FGameplayTag& WeaponTag, const TSubclassOf<UGameplayAbility>& LoadedAbility);

protected:
	void GivePlayerWeaponInternal(const TSubclassOf<UGameplayAbility>& AbilityClass);
	void BindAbilityCooldown(const FGameplayTag& WeaponTag);
	
	UFUNCTION()
	void HandleCooldownTagChanged(FGameplayTag GameplayTag, int Count);
};
