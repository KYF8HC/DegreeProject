#pragma once

#include "CoreMinimal.h"
#include "Characters/DP_BaseCharacter.h"
#include "GUI/WidgetController/DP_OverlayWidgetController.h"

#include "DP_EnemyCharacter.generated.h"

class ADP_AIController;
class UBehaviorTree;
enum class ECharacterClass : uint8;
class UWidgetComponent;

UCLASS()
class DEGREEPROJECT_API ADP_EnemyCharacter : public ADP_BaseCharacter
{
	GENERATED_BODY()

public:
	ADP_EnemyCharacter();

	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnAttributeChange OnHealthChangeDelegate;

	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnAttributeChange OnMaxHealthChangeDelegate;

	UFUNCTION(BlueprintImplementableEvent)
	void StartDefaultEvent();
	
	virtual void PossessedBy(AController* NewController) override;
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBarWidgetComponentRef{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI")
	TObjectPtr<UBehaviorTree> BehaviorTreeRef{};

	UPROPERTY()
	TObjectPtr<ADP_AIController> AIControllerRef{};
	
	virtual void BeginPlay() override;
};
