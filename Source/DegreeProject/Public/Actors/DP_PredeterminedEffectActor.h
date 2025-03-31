#pragma once

#include "CoreMinimal.h"
#include "DP_EffectActor.h"
#include "DP_PredeterminedEffectActor.generated.h"

UCLASS()
class DEGREEPROJECT_API ADP_PredeterminedEffectActor : public ADP_EffectActor
{
	GENERATED_BODY()

public:
	ADP_PredeterminedEffectActor();

	UFUNCTION(BlueprintCallable)
	bool ApplyEffectToTargetFromPredeterminedEffect(AActor* TargetActor,
	                                                TSubclassOf<UGameplayEffect> GameplayEffectClass, int32 ActorLevel);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Applied Effects")
	FGameplayEffectData GameplayEffectRef{};
	
	virtual bool OnOverlap(AActor* TargetActor) override;
	virtual bool OnEndOverlap(AActor* TargetActor) override;
};
