#include "Actors/DP_EffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Characters/DP_PlayerCharacter.h"
#include "GameFramework/PlayerState.h"


ADP_EffectActor::ADP_EffectActor()
{
	PrimaryActorTick.bCanEverTick = true;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("RootComponent"));
}

bool ADP_EffectActor::ApplyEffectToTarget(AActor* TargetActor, FGameplayEffectData GameplayEffect)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!IsValid(TargetASC))
		return false;

	checkf(GameplayEffect.GameplayEffectClassRef,
	       TEXT("ADP_EffectActor::ApplyEffectToTarget: GameplayEffectClass is nullptr"));

	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);

	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(
		GameplayEffect.GameplayEffectClassRef, 1, EffectContextHandle);

	const FActiveGameplayEffectHandle EffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(
		*EffectSpecHandle.Data.Get());

	if (GameplayEffect.DurationType == EEffectDurationType::Infinite &&
		GameplayEffect.RemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		FOverlappingActor OverlappingActor;
		OverlappingActor.OverlappingActorRef = TargetActor;

		if (EffectHandle.WasSuccessfullyApplied())
		{
			ActiveEffectHandles.Add(EffectHandle, TargetASC);
			OverlappingActor.bIsEffectApplied = true;
		}
		else
		{
			OverlappingActor.bIsEffectApplied = false;
		}

		OverlappingActor.OnAnyEffectRemovedHandle = TargetASC->OnAnyGameplayEffectRemovedDelegate().AddUObject(
			this, &ADP_EffectActor::OnAnyEffectRemoved);
		if (OverlappingActors.Contains(OverlappingActor) == false)
			OverlappingActors.Add(OverlappingActor);
	}
	return true;
}

void ADP_EffectActor::OnOverlap(AActor* TargetActor)
{
	if (GameplayEffectRef.ApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, GameplayEffectRef);
	}
}

void ADP_EffectActor::RemoveEffectFromTarget(AActor* TargetActor)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!IsValid(TargetASC))
		return;

	FOverlappingActor ActorToBeRemoved;
	for (auto Actor : OverlappingActors)
	{
		if (Actor.OverlappingActorRef == TargetActor)
		{
			ActorToBeRemoved = Actor;
			break;
		}
	}
	TargetASC->OnAnyGameplayEffectRemovedDelegate().Remove(ActorToBeRemoved.OnAnyEffectRemovedHandle);
	OverlappingActors.Remove(ActorToBeRemoved);

	TArray<FActiveGameplayEffectHandle> HandlesToRemove;

	for (auto HandlePair : ActiveEffectHandles)
	{
		if (TargetASC == HandlePair.Value)
		{
			TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
		}
		HandlesToRemove.Add(HandlePair.Key);

		break;
	}

	for (auto Handle : HandlesToRemove)
	{
		ActiveEffectHandles.Remove(Handle);
	}
}

void ADP_EffectActor::OnAnyEffectRemoved(const FActiveGameplayEffect& ActiveGameplayEffect)
{
	auto TargetActor = CastChecked<APlayerState>(
		ActiveGameplayEffect.Handle.GetOwningAbilitySystemComponent()->GetOwner())->GetPawn();
	UE_LOG(LogTemp, Log, TEXT("%s: Effect removed from %s"), *GetName(), *TargetActor->GetName());

	for (auto Actor : OverlappingActors)
	{
		if (Actor.OverlappingActorRef == TargetActor &&
			Actor.bIsEffectApplied == false)
		{
			Actor.bIsEffectApplied = ApplyEffectToTarget(Actor.OverlappingActorRef, GameplayEffectRef);
			UE_LOG(LogTemp, Log, TEXT("%s: Applying effect to %s, %s"), *GetName(),
			       *Actor.OverlappingActorRef->GetName(), Actor.bIsEffectApplied ? TEXT("Success") : TEXT("Failed"));
		}
	}
}

void ADP_EffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (GameplayEffectRef.ApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, GameplayEffectRef);
	}
	if (GameplayEffectRef.RemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UE_LOG(LogTemp, Log, TEXT("%s: Effect getting removed"), *GetName())

		ADP_PlayerCharacter* PlayerCharacter = Cast<ADP_PlayerCharacter>(TargetActor);
		if (!PlayerCharacter)
			return;
		RemoveEffectFromTarget(TargetActor);
	}
}
