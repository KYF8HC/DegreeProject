#include "Core/Events/DP_EventHandler.h"
#include "Core/Events/DP_Event.h"
#include "DegreeProject/DegreeProject.h"

UDP_EventHandler::UDP_EventHandler()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDP_EventHandler::PushEvent(TScriptInterface<IDP_Event> Event)
{
	if (!Event)
		return;

	////Are you a client?
	//if (!GetOwner()->HasAuthority())
	//	ServerPushEvent(Event.GetObject());

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
		LogOnScreen(this, EventMessage, FColor::Red, 0.0f);
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
		
		if (bShouldLogEvents)
		{
			UE_LOG(LogTemp, Log, TEXT("Current Event: %s is done: %d"), *CurrentEvent.GetObject()->GetName(),
			   CurrentEvent->IsDone());
		}
		
		CurrentEvent->OnUpdate();
		if (!EventStack.IsEmpty() && EventStack[0] == CurrentEvent)
		{
			if (CurrentEvent->IsDone())
			{
				UE_LOG(LogTemp, Log, TEXT("Current Event: %s is done"), *CurrentEvent.GetObject()->GetName());
				CurrentEvent->OnEnd();
				StartedEvents.Remove(CurrentEvent.GetObject());
				EventStack.RemoveAt(0);
				CurrentEvent = nullptr;
			}
		}
	}
}

//void UDP_EventHandler::ServerPushEvent_Implementation(UObject* Event)
//{
//	if (Event)
//	{
//		UClass* EventClass = Event->GetClass();
//		if (EventClass->ImplementsInterface(UDP_Event::StaticClass()))
//		{
//			TScriptInterface<IDP_Event> EventInterface;
//			EventInterface.SetObject(Event);
//			PushEvent(EventInterface);
//		}
//	}
//}
