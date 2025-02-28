#include "Core/Events/AI/DP_AIPatrolEvent.h"
#include "Runtime/AIModule/Classes/AIController.h"

UDP_AIPatrolEvent::UDP_AIPatrolEvent()
{
}


void UDP_AIPatrolEvent::OnBegin(bool bFirstTime)
{
	bShouldMove = true;
	if (bFirstTime && PatrolPath.Num() > 0)
		TargetLocation = PatrolPath[0];
}

void UDP_AIPatrolEvent::OnUpdate()
{
	if (ControllerRef && bShouldMove)
		ControllerRef->MoveToLocation(TargetLocation);

	if (ControllerRef->GetPawn()->GetActorLocation().Equals(TargetLocation, 50.0f))
	{
		TargetLocation = PatrolPath[FMath::RandRange(0, PatrolPath.Num() - 1)];
	}
}

void UDP_AIPatrolEvent::OnEnd()
{
	bShouldMove = false;
}

bool UDP_AIPatrolEvent::IsDone()
{
	return false;
}

