#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "DP_AbilitySystemComponent.generated.h"

UCLASS()
class DEGREEPROJECT_API UDP_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Ability System")
	TObjectPtr<AActor> TargetActorRef{};
	
};
