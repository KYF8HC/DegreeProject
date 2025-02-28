#pragma once

#include "CoreMinimal.h"
#include "Characters/DP_BaseCharacter.h"
#include "GUI/WidgetController/DP_OverlayWidgetController.h"

#include "DP_EnemyCharacter.generated.h"

enum class ECharacterClass : uint8;
class UWidgetComponent;
class UDP_AIPatrolEvent;
class UDP_AIBaseEvent;
class IDP_Event;
class UDP_EventHandler;

UCLASS()
class DEGREEPROJECT_API ADP_EnemyCharacter : public ADP_BaseCharacter
{
	GENERATED_BODY()

public:
	ADP_EnemyCharacter();

	UFUNCTION(BlueprintImplementableEvent)
	void StartDefaultEvent();

	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnAttributeChange OnHealthChangeDelegate;

	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnAttributeChange OnMaxHealthChangeDelegate;
	
protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Events")
	TObjectPtr<UDP_EventHandler> EnemyEventHandlerRef{};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Events")
	TArray<FVector> PatrolPath{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Events")
	TSubclassOf<UDP_AIBaseEvent> DefaultEventClass{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBarWidgetComponentRef{};
	
	UPROPERTY(BlueprintReadOnly, Category="AI", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UDP_AIPatrolEvent> MoveEventRef{};

	
	virtual void BeginPlay() override;
};
