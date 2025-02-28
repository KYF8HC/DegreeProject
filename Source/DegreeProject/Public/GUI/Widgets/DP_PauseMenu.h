#pragma once

#include "CoreMinimal.h"
#include "DP_EventUserWidgetBase.h"
#include "DP_PauseMenu.generated.h"

UCLASS()
class DEGREEPROJECT_API UDP_PauseMenu : public UDP_EventUserWidgetBase
{
	GENERATED_BODY()

public:
	virtual void OnBegin(bool bFirstTime) override;
	virtual void OnUpdate() override;
	virtual void OnEnd() override;
	virtual bool IsDone() override;

protected:

	UPROPERTY(BlueprintReadWrite, Category="Pause Menu")
	bool bIsDone = false;
};
