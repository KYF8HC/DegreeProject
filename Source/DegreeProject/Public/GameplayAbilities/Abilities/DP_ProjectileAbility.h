﻿#pragma once

#include "CoreMinimal.h"
#include "DP_DamageGameplayAbility.h"
#include "GameplayAbilities/Abilities/DP_GameplayAbility.h"
#include "DP_ProjectileAbility.generated.h"

class ADP_Projectile;

UCLASS()
class DEGREEPROJECT_API UDP_ProjectileAbility : public UDP_DamageGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ProjectileClass", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ADP_Projectile> ProjectileClass{};
};
