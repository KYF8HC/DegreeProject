#include "Core/Events/DP_EventHandler.h"
#include "Core/Events/DP_Event.h"

UDP_EventHandler::UDP_EventHandler()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDP_EventHandler::PushEvent(TScriptInterface<IDP_Event> Event)
{
	if (!Event)
		return;

	//already in stack
	EventStack.RemoveAll([Event](const TScriptInterface<IDP_Event>& e)
	{
		return e == Event;
	});

	//insert event
	EventStack.Insert(Event, 0);

	//reset current event
	if (CurrentEvent != nullptr &&
		CurrentEvent.GetObject() != nullptr &&
		CurrentEvent != Event)
	{
		CurrentEvent = nullptr;
	}
}

void UDP_EventHandler::RemoveEvent(TScriptInterface<IDP_Event> Event)
{
	if (!Event || !EventStack.Contains(Event))
		return;

	if (Event == CurrentEvent || StartedEvents.Contains(Event.GetObject()))
	{
		Event->OnEnd();
		StartedEvents.Remove(Event.GetObject());
	}

	EventStack.Remove(Event);
}

void UDP_EventHandler::TickComponent(float DeltaTime, enum ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateEvents();

	if (CurrentEvent.GetObject() != nullptr)
	{
		const FString EventMessage = FString::Printf(TEXT("Current Event: %s"), *CurrentEvent.GetObject()->GetName());
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, EventMessage);
	}
}

void UDP_EventHandler::UpdateEvents()
{
	if (EventStack.Num() == 0)
		return;

	if (CurrentEvent.GetObject() == nullptr)
	{
		StartedEvents.Remove(nullptr);
		CurrentEvent = EventStack[0];
		bool bFirstTime = !StartedEvents.Contains(CurrentEvent.GetObject());
		StartedEvents.Add(CurrentEvent.GetObject());
		CurrentEvent->OnBegin(bFirstTime);

		if (!EventStack.IsEmpty() && EventStack[0] != CurrentEvent)
		{
			CurrentEvent = nullptr;
			UpdateEvents();
		}
	}

	if (CurrentEvent.GetObject())
	{
		CurrentEvent->OnUpdate();
		if (!EventStack.IsEmpty() && EventStack[0] == CurrentEvent)
		{
			if (CurrentEvent->IsDone())
			{
				CurrentEvent->OnEnd();
				StartedEvents.Remove(CurrentEvent.GetObject());
				EventStack.RemoveAt(0);
				CurrentEvent = nullptr;
			}
		}
	}
}
