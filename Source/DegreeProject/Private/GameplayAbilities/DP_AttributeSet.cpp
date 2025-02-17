#include "GameplayAbilities/DP_AttributeSet.h"
#include "Net/UnrealNetwork.h"

UDP_AttributeSet::UDP_AttributeSet()
{
	InitHealth(50.0f);
	InitMaxHealth(100.0f);
	InitAbilityResource(100.0f);
	InitMaxAbilityResource(100.0f);
}

void UDP_AttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UDP_AttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDP_AttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDP_AttributeSet, AbilityResource, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDP_AttributeSet, MaxAbilityResource, COND_None, REPNOTIFY_Always);
}

void UDP_AttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDP_AttributeSet, Health, OldHealth);
}

#pragma region OnRep Functions
	//IMPLEMENT_GAS_ATTRIBUTE(UDP_AttributeSet, Health)
	IMPLEMENT_GAS_ATTRIBUTE(UDP_AttributeSet, MaxHealth)
	IMPLEMENT_GAS_ATTRIBUTE(UDP_AttributeSet, AbilityResource)
	IMPLEMENT_GAS_ATTRIBUTE(UDP_AttributeSet, MaxAbilityResource)
#pragma endregion
