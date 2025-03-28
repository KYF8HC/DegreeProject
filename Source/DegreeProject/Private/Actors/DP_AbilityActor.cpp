#include "Actors/DP_AbilityActor.h"

ADP_AbilityActor::ADP_AbilityActor()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	SceneComponentRef = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponentRef);
}

void ADP_AbilityActor::InitializeAbilityActor()
{
	Ammo = MaxAmmo;
	bIsInitialized = true;
}

