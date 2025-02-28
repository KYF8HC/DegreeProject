#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DP_EventHandler.generated.h"


class IDP_Event;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DEGREEPROJECT_API UDP_EventHandler : public UActorComponent
{
	GENERATED_BODY()

public:
	UDP_EventHandler();

	UFUNCTION(BlueprintCallable)
	void PushEvent(TScriptInterface<IDP_Event> Event);

	UFUNCTION(BlueprintCallable)
	void RemoveEvent(TScriptInterface<IDP_Event> Event);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Events")
	bool bShouldLogEvents{false};
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Events")
	TArray<TScriptInterface<IDP_Event>> EventStack{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Events")
	TSet<UObject*> StartedEvents{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Events")
	TScriptInterface<IDP_Event> CurrentEvent{};
	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void UpdateEvents();

	
	//UFUNCTION(Server, Reliable)
	//void ServerPushEvent(UObject* Event);

private:

};
