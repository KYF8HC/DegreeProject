#include "Actors/DP_DamageEffectActor.h"

ADP_DamageEffectActor::ADP_DamageEffectActor()
{
}

bool ADP_DamageEffectActor::OnOverlap(AActor* TargetActor)
{
	return ApplyEffectToTarget(TargetActor, DamageEffectSpecHandle);
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
	return true;
}
