#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DP_DamageTextComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DEGREEPROJECT_API UDP_DamageTextComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetDamageText(float Damage, bool bIsDodgedHit, bool bIsCriticalHit);
};
