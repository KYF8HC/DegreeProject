#include "GUI/Widgets/DP_EventUserWidgetBase.h"

void UDP_EventUserWidgetBase::OnBegin(bool bFirstTime)
{
	OnBeginBP(bFirstTime);
}

void UDP_EventUserWidgetBase::OnUpdate()
{
	OnUpdateBP();
}

void UDP_EventUserWidgetBase::OnEnd()
{
	OnEndBP();
}

bool UDP_EventUserWidgetBase::IsDone()
{
	return false;
}
