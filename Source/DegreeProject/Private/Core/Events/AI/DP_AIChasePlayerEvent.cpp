#include "Core/Events/AI/DP_AIChasePlayerEvent.h"
#include "AIController.h"
#include "Core/Events/AI/DP_AIAttackEvent.h"

UDP_AIChasePlayerEvent::UDP_AIChasePlayerEvent()
{
}

void UDP_AIChasePlayerEvent::OnBegin(bool bFirstTime)
{
	bShouldChase = true;
}

void UDP_AIChasePlayerEvent::OnUpdate()
{	
	if (TargetActorRef && bShouldChase)
	{
		ControllerRef->MoveToActor(TargetActorRef);
	}
}

void UDP_AIChasePlayerEvent::OnEnd()
{
	TargetActorRef = nullptr;
}

bool UDP_AIChasePlayerEvent::IsDone()
{
	//Doesn't work atm, eyesight is always nullptr 
	bool bLineOfSight = !ControllerRef->LineOfSightTo(TargetActorRef);
	return false;
}
