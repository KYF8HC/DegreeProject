#include "GUI/Widgets/DP_PauseMenu.h"

void UDP_PauseMenu::OnBegin(bool bFirstTime)
{
	Super::OnBegin(bFirstTime);
	GetOwningPlayer()->Pause();
	EnableWidget(true);
	bIsDone = false;
}

void UDP_PauseMenu::OnUpdate()
{
	Super::OnUpdate();
}

void UDP_PauseMenu::OnEnd()
{
	Super::OnEnd();
	GetOwningPlayer()->Pause();
	EnableWidget(false);
}

bool UDP_PauseMenu::IsDone()
{
	return bIsDone;
}
