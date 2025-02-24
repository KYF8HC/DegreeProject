#pragma once

#include "CoreMinimal.h"
#include "Characters/DP_BaseCharacter.h"
#include "DP_EnemyCharacter.generated.h"

class UDP_AIMoveEvent;
class UDP_AIBaseEvent;
class IDP_Event;
class UDP_EventHandler;

UCLASS()
class DEGREEPROJECT_API ADP_EnemyCharacter : public ADP_BaseCharacter
{
	GENERATED_BODY()

public:
	ADP_EnemyCharacter();
	void StartDefaultEvent();

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Events")
	TObjectPtr<UDP_EventHandler> EnemyEventHandlerRef{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Events")
	TArray<FVector> PatrolPath{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Events")
	TSubclassOf<UDP_AIBaseEvent> DefaultEventClass{};

	UPROPERTY(BlueprintReadOnly, Category="AI", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UDP_AIMoveEvent> MoveEventRef{};
	
	UFUNCTION()
	void OnBegin(bool bFirstTime);
	
	virtual void BeginPlay() override;
};
