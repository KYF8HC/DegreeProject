#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DP_AIController.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;

UCLASS()
class DEGREEPROJECT_API ADP_AIController : public AAIController
{
	GENERATED_BODY()

public:
	ADP_AIController();

protected:
	
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponentRef{};
};
