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
	if (!ControllerRef->LineOfSightTo(TargetRef))
	{
		ControllerRef->StopMovement();
		EventHandlerRef->RemoveEvent(this);
		return;
	}
	
	if (TargetRef && bShouldChase)
	{
		ControllerRef->MoveToActor(TargetRef);
	}

	if (FVector::Distance(ControllerRef->GetPawn()->GetActorLocation(), TargetRef->GetActorLocation()) < AttackRange)
	{
		ControllerRef->StopMovement();

		const TScriptInterface<UDP_AIAttackEvent> AttackEvent = NewObject<UDP_AIAttackEvent>(
			ControllerRef, AttackEventClass);
		AttackEvent->SetController(ControllerRef);
		AttackEvent->SetEventHandler(EventHandlerRef);
		AttackEvent->PreviousEvent = this;
		
		EventHandlerRef->PushEvent(AttackEvent);
		EventHandlerRef->RemoveEvent(this);
	}
}

void UDP_ChasePlayerEvent::OnEnd()
{
	TargetRef = nullptr;
}

bool UDP_ChasePlayerEvent::IsDone()
{
	return true;
}
