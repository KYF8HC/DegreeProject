#pragma once

#include "CoreMinimal.h"
#include "DP_AIBaseEvent.h"
#include "DP_AIAttackEvent.generated.h"

UCLASS()
class DEGREEPROJECT_API UDP_AIAttackEvent : public UDP_AIBaseEvent
{
	GENERATED_BODY()

public:
	
	UDP_AIAttackEvent();
	
	virtual void OnBegin(bool bFirstTime) override;
	virtual void OnUpdate() override;
	virtual void OnEnd() override;
	virtual bool IsDone() override;

	UPROPERTY()
	TScriptInterface<IDP_Event> PreviousEvent{};
};
