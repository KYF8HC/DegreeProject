#pragma once

#include "CoreMinimal.h"
#include "Core/Events/DP_Event.h"
#include "UObject/Object.h"
#include "DP_AIBaseEvent.generated.h"

class UDP_EventHandler;
class AAIController;

UCLASS(BlueprintType, Blueprintable)
class DEGREEPROJECT_API UDP_AIBaseEvent : public UObject, public IDP_Event
{
	GENERATED_BODY()
	
public:

	UDP_AIBaseEvent();
	
	virtual void OnBegin(bool bFirstTime) override;
	virtual void OnUpdate() override;
	virtual void OnEnd() override;
	virtual bool IsDone() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnBeginBP();
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnUpdateBP();

	UFUNCTION(BlueprintImplementableEvent)
	void OnEndBP();

	UFUNCTION(BlueprintCallable)
	void SetController(AAIController* Controller) { ControllerRef = Controller; }

	UFUNCTION(BlueprintCallable)
	void SetEventHandler(UDP_EventHandler* EventHandler) { EventHandlerRef = EventHandler; }

protected:

	UPROPERTY(BlueprintReadOnly, Category="AI", meta=(AllowPrivateAccess="true"))
	TObjectPtr<AAIController> ControllerRef{};

	UPROPERTY(BlueprintReadOnly, Category="AI", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UDP_EventHandler> EventHandlerRef{};
};
