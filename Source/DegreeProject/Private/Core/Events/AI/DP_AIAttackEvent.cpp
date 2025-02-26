#include "Core/Events/AI/DP_AIAttackEvent.h"

#include "AIController.h"

UDP_AIAttackEvent::UDP_AIAttackEvent()
{
}

void UDP_AIAttackEvent::OnBegin(bool bFirstTime)
{
	Super::OnBegin(bFirstTime);
	
}

void UDP_AIAttackEvent::OnUpdate()
{
	Super::OnUpdate();
}

void UDP_AIAttackEvent::OnEnd()
{
	Super::OnEnd();
}

bool UDP_AIAttackEvent::IsDone()
{
	const bool bIsWithinRange = ControllerRef->GetPawn()->GetDistanceTo(TargetActorRef) > AttackRange;
	return bIsWithinRange;
}
