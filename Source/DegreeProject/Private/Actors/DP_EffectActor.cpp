#include "Actors/DP_EffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Interaction/CombatInterface.h"

ADP_EffectActor::ADP_EffectActor()
{
	PrimaryActorTick.bCanEverTick = true;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("RootComponent"));
}

bool ADP_EffectActor::ApplyEffectToTarget(AActor* TargetActor,
                                          const FGameplayEffectSpecHandle& InGameplayEffectSpecHandle)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr) return false;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(TargetActor);
	if (CombatInterface)
	{
		if (CombatInterface->IsEnemy() && !bApplyEffectToEnemies) return false;
		if (!CombatInterface->IsEnemy() && !bApplyEffectToPlayer) return false;
	}
	
	const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(
		*InGameplayEffectSpecHandle.Data.Get());
	const bool bIsInfinite = InGameplayEffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy ==
		EGameplayEffectDurationType::Infinite;
	if (bIsInfinite)
	{
		ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
	}

	return true;
}

bool ADP_EffectActor::OnOverlap(AActor* TargetActor)
{
	return false;
}

void ADP_EffectActor::RemoveEffectFromTarget(AActor* TargetActor)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!IsValid(TargetASC)) return;

	TArray<FActiveGameplayEffectHandle> HandlesToRemove;
	for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair : ActiveEffectHandles)
	{
		if (TargetASC == HandlePair.Value)
		{
			TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
			HandlesToRemove.Add(HandlePair.Key);
		}
	}
	for (FActiveGameplayEffectHandle& Handle : HandlesToRemove)
	{
		ActiveEffectHandles.FindAndRemoveChecked(Handle);
	}
}

void ADP_EffectActor::RemoveEveryEffect()
{
	for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair : ActiveEffectHandles)
	{
		HandlePair.Value->RemoveActiveGameplayEffect(HandlePair.Key, 1);
	}

	ActiveEffectHandles.Empty();
}

bool ADP_EffectActor::OnEndOverlap(AActor* TargetActor)
{
	return false;
}
