#pragma once

#include "CoreMinimal.h"
#include "DP_AIBaseEvent.h"
#include "GameplayTagContainer.h"
#include "DP_AIAttackEvent.generated.h"

class UDP_GameplayAbility;
class UDP_AbilitySystemComponent;

UCLASS()
class DEGREEPROJECT_API UDP_AIAttackEvent : public UDP_AIBaseEvent
{
	GENERATED_BODY()

public:
	
	UDP_AIAttackEvent();
	
	virtual void OnBegin(bool bFirstTime) override;
	virtual void OnUpdate() override;
	virtual void OnEnd() override;
	virtual bool IsDone() override;

	UFUNCTION(BlueprintCallable)
	void SetTargetActorRef(AActor* TargetActor) { TargetActorRef = TargetActor; }

	UPROPERTY(BlueprintReadWrite, Category="AI")
	bool bIsDone{false};

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Ability System")
	TObjectPtr<UDP_AbilitySystemComponent> AbilitySystemComponentRef{};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI")
	FGameplayTag AttackAbilityTag;
	
	UPROPERTY(BlueprintReadOnly, Category="AI")
	TObjectPtr<AActor> TargetActorRef{};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI")
	float AttackRange{130.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Ability")
	float AttackCooldown{2.0f};

	bool bCanAttack{true};

};
