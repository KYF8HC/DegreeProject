#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DP_EffectActor.generated.h"

class UGameplayEffect;

UCLASS()
class DEGREEPROJECT_API ADP_EffectActor : public AActor
{
	GENERATED_BODY()

public:
	ADP_EffectActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffect;
};
