#include "Player/DP_PlayerState.h"
#include "GameplayAbilities/DP_AbilitySystemComponent.h"
#include "GameplayAbilities/DP_AttributeSet.h"

ADP_PlayerState::ADP_PlayerState()
{
	SetNetUpdateFrequency(100.0f);

	AbilitySystemComponentRef = CreateDefaultSubobject<UDP_AbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponentRef->SetIsReplicated(true);
	AbilitySystemComponentRef->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSetRef = CreateDefaultSubobject<UDP_AttributeSet>(TEXT("AttributeSet"));
}

UAbilitySystemComponent* ADP_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponentRef;
}
