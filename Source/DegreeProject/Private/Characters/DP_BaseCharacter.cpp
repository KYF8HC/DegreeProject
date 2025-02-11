#include "Characters/DP_BaseCharacter.h"

ADP_BaseCharacter::ADP_BaseCharacter()
{
 	PrimaryActorTick.bCanEverTick = false;
}

UAbilitySystemComponent* ADP_BaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponentRef;
}

void ADP_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


