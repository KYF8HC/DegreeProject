#include "Actors/DP_PredeterminedEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"


ADP_PredeterminedEffectActor::ADP_PredeterminedEffectActor()
{
}

bool ADP_PredeterminedEffectActor::ApplyEffectToTargetFromPredeterminedEffect(
	AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass, int32 ActorLevel)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr) return false;

	check(GameplayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(
		GameplayEffectClass, ActorLevel, EffectContextHandle);

	return ApplyEffectToTarget(TargetActor, EffectSpecHandle);
}

bool ADP_PredeterminedEffectActor::OnOverlap(AActor* TargetActor)
{
	if (GameplayEffectRef.ApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		bool bIsSuccessfulApplication = ApplyEffectToTargetFromPredeterminedEffect(TargetActor, GameplayEffectRef.GameplayEffectClassRef, 1);
		OverlappingActors.Add({TargetActor, bIsSuccessfulApplication});
		return bIsSuccessfulApplication;
	}
	return false;
}

bool ADP_PredeterminedEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (GameplayEffectRef.ApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		return ApplyEffectToTargetFromPredeterminedEffect(TargetActor, GameplayEffectRef.GameplayEffectClassRef, 1);
	}
	if (GameplayEffectRef.RemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UE_LOG(LogTemp, Log, TEXT("%s: Effect getting removed"), *GetName())
		RemoveEffectFromTarget(TargetActor);
	}

	FOverlappingActor ActorToRemove;
	for (FOverlappingActor OverlappingActor : OverlappingActors)
	{
		if (OverlappingActor.OverlappingActorRef == TargetActor)
		{
			ActorToRemove = OverlappingActor;
		}
	}
	OverlappingActors.Remove(ActorToRemove);
	return true;
}
