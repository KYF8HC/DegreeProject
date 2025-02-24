#include "Core/Events/AI/DP_AIMoveEvent.h"
#include "Runtime/AIModule/Classes/AIController.h"

UDP_AIMoveEvent::UDP_AIMoveEvent()
{
}


void UDP_AIMoveEvent::OnBegin(bool bFirstTime)
{
	bShouldMove = true;
	if (bFirstTime && PatrolPath.Num() > 0)
		TargetLocation = PatrolPath[0];
}

void UDP_AIMoveEvent::OnUpdate()
{
	UE_LOG(LogTemp, Warning, TEXT("Moving to location"));
	if (ControllerRef && bShouldMove)
		ControllerRef->MoveToLocation(TargetLocation);

	if (ControllerRef->GetPawn()->GetActorLocation().Equals(TargetLocation, 50.0f))
	{
		TargetLocation = PatrolPath[FMath::RandRange(0, PatrolPath.Num() - 1)];
	}
}

void UDP_AIMoveEvent::OnEnd()
{
	bShouldMove = false;
}

bool UDP_AIMoveEvent::IsDone()
{
	return false;
}

