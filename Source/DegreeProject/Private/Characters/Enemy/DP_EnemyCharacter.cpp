#include "Characters/Enemy/DP_EnemyCharacter.h"
#include "GameplayAbilities/DP_AbilitySystemComponent.h"
#include "GameplayAbilities/DP_AttributeSet.h"


ADP_EnemyCharacter::ADP_EnemyCharacter()
{
	AbilitySystemComponentRef = CreateDefaultSubobject<UDP_AbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponentRef->SetIsReplicated(true);
	AbilitySystemComponentRef->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSetRef = CreateDefaultSubobject<UDP_AttributeSet>(TEXT("AttributeSet"));
}

void ADP_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponentRef->InitAbilityActorInfo(this, this);
}
