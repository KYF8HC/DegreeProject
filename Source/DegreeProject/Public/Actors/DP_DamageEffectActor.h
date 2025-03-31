#pragma once

#include "CoreMinimal.h"
#include "DP_EffectActor.h"
#include "DP_DamageEffectActor.generated.h"

UCLASS()
class DEGREEPROJECT_API ADP_DamageEffectActor : public ADP_EffectActor
{
	GENERATED_BODY()

public:
	ADP_DamageEffectActor();
	
	UPROPERTY(BlueprintReadWrite, Category = "Damage", meta = (ExposeOnSpawn = "true"))
	FGameplayEffectSpecHandle DamageEffectSpecHandle{};
	
protected:

	virtual bool OnOverlap(AActor* TargetActor) override;
	virtual bool OnEndOverlap(AActor* TargetActor) override;
	
	
};
