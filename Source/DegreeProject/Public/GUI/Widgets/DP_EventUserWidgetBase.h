#pragma once

#include "CoreMinimal.h"
#include "DP_UserWidgetBase.h"
#include "Core/Events/DP_Event.h"
#include "DP_EventUserWidgetBase.generated.h"

UCLASS()
class DEGREEPROJECT_API UDP_EventUserWidgetBase : public UDP_UserWidgetBase, public IDP_Event
{
	GENERATED_BODY()

public:
	virtual void OnBegin(bool bFirstTime) override;
	virtual void OnUpdate() override;
	virtual void OnEnd() override;
	virtual bool IsDone() override;

protected:

	UFUNCTION(BlueprintImplementableEvent, Category="Widget Events")
	void OnBeginBP(bool bFirstTime);

	UFUNCTION(BlueprintImplementableEvent, Category="Widget Events")
	void OnUpdateBP();

	UFUNCTION(BlueprintImplementableEvent, Category="Widget Events")
	void OnEndBP();
};
