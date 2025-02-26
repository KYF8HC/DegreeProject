#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DP_GameplayAbility.generated.h"


UCLASS()
class DEGREEPROJECT_API UDP_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, Category="Input")
	FGameplayTag StartupInputTag;
};
