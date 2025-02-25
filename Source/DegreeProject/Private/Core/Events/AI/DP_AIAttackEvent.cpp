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
	const FString EventMessage = FString::Printf(TEXT("Attacking Player"));
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Green, EventMessage);
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
