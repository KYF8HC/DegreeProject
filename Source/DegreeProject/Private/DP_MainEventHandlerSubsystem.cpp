#include "DP_MainEventHandlerSubsystem.h"
#include "Core/Events/DP_EventHandler.h"

UDP_EventHandler* UDP_MainEventHandlerSubsystem::GetMainEventHandler()
{
	if (MainEventHandlerRef == nullptr)
	{
		AActor* EventHandlerActor = GetWorld()->SpawnActor<AActor>();

		MainEventHandlerRef = NewObject<UDP_EventHandler>(EventHandlerActor);
		EventHandlerActor->AddOwnedComponent(MainEventHandlerRef);
		MainEventHandlerRef->RegisterComponent();
		MainEventHandlerRef->SetTickableWhenPaused(true);
	}

	return MainEventHandlerRef;
}

void UDP_MainEventHandlerSubsystem::ClearMainEventHandler()
{
	if (MainEventHandlerRef)
	{
		MainEventHandlerRef->GetOwner()->Destroy();
		MainEventHandlerRef = nullptr;
	}
}

void UDP_MainEventHandlerSubsystem::Deinitialize()
{
	Super::Deinitialize();
	ClearMainEventHandler();
}
