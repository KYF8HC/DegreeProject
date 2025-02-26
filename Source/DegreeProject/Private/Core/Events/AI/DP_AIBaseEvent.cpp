#include "Core/Events/AI/DP_AIBaseEvent.h"

UDP_AIBaseEvent::UDP_AIBaseEvent()
{
}

void UDP_AIBaseEvent::OnBegin(bool bFirstTime)
{
	OnBeginBP();
}

void UDP_AIBaseEvent::OnUpdate()
{
	OnUpdateBP();
}

void UDP_AIBaseEvent::OnEnd()
{
	OnEndBP();
}

bool UDP_AIBaseEvent::IsDone()
{
	return false;
}
