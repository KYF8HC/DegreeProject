#include "Core/Events/AI/DP_ChasePlayerEvent.h"

#include "AIController.h"
#include "Core/Events/DP_EventHandler.h"
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
	if (!ControllerRef->LineOfSightTo(TargetActorRef))
	{
		ControllerRef->StopMovement();
		EventHandlerRef->RemoveEvent(this);
		return;
	}
	
	if (TargetActorRef && bShouldChase)
	{
		ControllerRef->MoveToActor(TargetActorRef);
	}

	if (ControllerRef->GetPawn()->GetDistanceTo(TargetActorRef) < AttackRange)
	{
		ControllerRef->StopMovement();

		const TScriptInterface<UDP_AIAttackEvent> AttackEvent = NewObject<UDP_AIAttackEvent>(
			ControllerRef, AttackEventClass);
		AttackEvent->SetController(ControllerRef);
		AttackEvent->SetEventHandler(EventHandlerRef);
		AttackEvent->PreviousEvent = this;
		AttackEvent->TargetActorRef = TargetActorRef;
		
		EventHandlerRef->PushEvent(AttackEvent);
	}
}

void UDP_ChasePlayerEvent::OnEnd()
{
	TargetActorRef = nullptr;
}

bool UDP_ChasePlayerEvent::IsDone()
{
	return false;
}
