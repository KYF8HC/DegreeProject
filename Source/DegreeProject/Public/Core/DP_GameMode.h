#pragma once

#include "CoreMinimal.h"
#include "Events/DP_Event.h"
#include "GameFramework/GameModeBase.h"
#include "DP_GameMode.generated.h"

class ADP_PlayerCharacter;
class ADP_PlayerHUD;
class ADP_PlayerController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeginDelegate, bool, bFirstTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdateDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndDelegate);

UCLASS(Abstract)
class DEGREEPROJECT_API ADP_GameMode : public AGameModeBase, public IDP_Event
{
	GENERATED_BODY()

public:

	ADP_GameMode();

	UPROPERTY(BlueprintAssignable)
	FOnBeginDelegate OnBeginDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnUpdateDelegate OnUpdateDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnEndDelegate OnEndDelegate;
	
	virtual void OnBegin(bool bFirstTime) override;
	virtual void OnUpdate() override;
	virtual void OnEnd() override;
	virtual bool IsDone() override;

private:
	
	UPROPERTY(BlueprintReadOnly, Category="Player Systems", meta=(AllowPrivateAccess="true"))
	TArray<TObjectPtr<ADP_PlayerController>> PlayerControllers{};
};
