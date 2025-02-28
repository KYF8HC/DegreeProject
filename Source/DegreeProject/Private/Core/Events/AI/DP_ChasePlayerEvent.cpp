#include "Core/Events/AI/DP_ChasePlayerEvent.h"
#include "AIController.h"
#include "Core/Events/AI/DP_AIAttackEvent.h"

UDP_ChasePlayerEvent::UDP_ChasePlayerEvent()
{
}

void UDP_ChasePlayerEvent::OnBegin(bool bFirstTime)
{
	bShouldChase = true;
}

void UDP_ChasePlayerEvent::OnUpdate()
{	
	if (TargetActorRef && bShouldChase)
	{
		ControllerRef->MoveToActor(TargetActorRef);
	}
}

void UDP_ChasePlayerEvent::OnEnd()
{
	TargetActorRef = nullptr;
}

bool UDP_ChasePlayerEvent::IsDone()
{
	//Doesn't work atm, eyesight is always nullptr 
	bool bLineOfSight = !ControllerRef->LineOfSightTo(TargetActorRef);
	return false;
}
