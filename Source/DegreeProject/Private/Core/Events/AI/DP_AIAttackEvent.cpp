#include "Core/Events/AI/DP_AIAttackEvent.h"

UDP_AIAttackEvent::UDP_AIAttackEvent()
{
}

void UDP_AIAttackEvent::OnBegin(bool bFirstTime)
{
	Super::OnBegin(bFirstTime);
	
}

void UDP_AIAttackEvent::OnUpdate()
{
	if (!bCanAttack)
		return;

	OnUpdateBP();
	
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
	{
		bCanAttack = true;
	}, AttackCooldown, false);

	bCanAttack = false;
}

void UDP_AIAttackEvent::OnEnd()
{
	Super::OnEnd();
}

bool UDP_AIAttackEvent::IsDone()
{
	return bIsDone;
}
