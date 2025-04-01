#include "Actors/DP_DamageEffectActor.h"

ADP_DamageEffectActor::ADP_DamageEffectActor()
{
}

bool ADP_DamageEffectActor::OnOverlap(AActor* TargetActor)
{
	return ApplyEffectToTarget(TargetActor, DamageEffectSpecHandle);
}

void ADP_DamageEffectActor::InitializeAbilityActor()
{
	Ammo = MaxAmmo;
	bIsInitialized = true;
}

void ADP_DamageEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
		
	if (!bIsInitialized)
		return;
	
	Ammo -= DeltaTime;
	if (Ammo <= 0.0f)
	{
		Destroy();
		OnEffectOutOfAmmo.Broadcast();
	}
}

bool ADP_DamageEffectActor::OnEndOverlap(AActor* TargetActor)
{
	RemoveEffectFromTarget(TargetActor);

	FOverlappingActor ActorToRemove;
	for (FOverlappingActor OverlappingActor : OverlappingActors)
	{
		if (OverlappingActor.OverlappingActorRef == TargetActor)
		{
			ActorToRemove = OverlappingActor;
		}
	}
	OverlappingActors.Remove(ActorToRemove);
	if (ActorToRemove.VisualEffectActorRef != nullptr)
		ActorToRemove.VisualEffectActorRef->Destroy();
	return true;
}
