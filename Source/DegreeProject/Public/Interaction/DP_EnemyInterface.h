#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DP_EnemyInterface.generated.h"

UINTERFACE()
class UDP_EnemyInterface : public UInterface
{
	GENERATED_BODY()
};


class DEGREEPROJECT_API IDP_EnemyInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Combat")
	void SetCombatTarget(AActor* InCombatTarget);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Combat")
	AActor* GetCombatTarget() const;
};
