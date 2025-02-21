#pragma once

#include "CoreMinimal.h"
#include "Events/DP_Event.h"
#include "GameFramework/GameModeBase.h"
#include "DP_GameMode.generated.h"

class ADP_PlayerCharacter;
class ADP_PlayerHUD;
class ADP_PlayerController;

UCLASS(Abstract)
class DEGREEPROJECT_API ADP_GameMode : public AGameModeBase, public IDP_Event
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

private:
	
	UPROPERTY(BlueprintReadOnly, Category="Player Systems", meta=(AllowPrivateAccess="true"))
	TObjectPtr<ADP_PlayerController> PlayerControllerRef{};

	UPROPERTY(BlueprintReadOnly, Category="Player Systems", meta=(AllowPrivateAccess="true"))
	TObjectPtr<ADP_PlayerHUD> PlayerHUDRef{};
};
