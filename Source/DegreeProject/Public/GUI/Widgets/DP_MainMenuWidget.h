#pragma once

#include "CoreMinimal.h"
#include "DP_EventUserWidgetBase.h"
#include "DP_MainMenuWidget.generated.h"

UCLASS()
class DEGREEPROJECT_API UDP_MainMenuWidget : public UDP_EventUserWidgetBase
{
	GENERATED_BODY()

public:
	virtual void OnBegin(bool bFirstTime) override;
	virtual void OnEnd() override;
	virtual bool IsDone() override;

protected:
	
	virtual void NativeConstruct() override;

private:
	UFUNCTION(BlueprintCallable)
	void OnStartGame();
};
