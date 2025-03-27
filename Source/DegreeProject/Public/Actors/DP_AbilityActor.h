#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "DP_AbilityActor.generated.h"

UCLASS()
class DEGREEPROJECT_API ADP_AbilityActor : public AActor
{
	GENERATED_BODY()

public:
	ADP_AbilityActor();
	
	UPROPERTY(BlueprintReadWrite, Category = "Damage", meta = (ExposeOnSpawn = "true"))
	FGameplayEffectSpecHandle DamageEffectSpecHandle{};
};
