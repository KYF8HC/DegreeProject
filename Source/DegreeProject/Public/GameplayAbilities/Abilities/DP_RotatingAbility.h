#pragma once

#include "CoreMinimal.h"
#include "DP_DamageGameplayAbility.h"
#include "DP_RotatingAbility.generated.h"

class ADP_RotatingWeaponActor;

UCLASS()
class DEGREEPROJECT_API UDP_RotatingAbility : public UDP_DamageGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ProjectileClass", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ADP_RotatingWeaponActor> RotatingActorClass{};
};
