#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DP_MainEventHandlerSubsystem.generated.h"

class UDP_EventHandler;

UCLASS()
class DEGREEPROJECT_API UDP_MainEventHandlerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Events")
	UDP_EventHandler* GetMainEventHandler();

	void ClearMainEventHandler();
	virtual void Deinitialize() override;

private:
	
	UPROPERTY(BlueprintReadOnly, Category="Events", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UDP_EventHandler> MainEventHandlerRef{};
	
};
