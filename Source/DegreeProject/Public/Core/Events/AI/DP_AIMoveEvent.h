#pragma once

#include "CoreMinimal.h"
#include "DP_AIBaseEvent.h"
#include "DP_AIMoveEvent.generated.h"

class AAIController;
class UCharacterMovementComponent;

UCLASS(BlueprintType, Blueprintable)
class DEGREEPROJECT_API UDP_AIMoveEvent : public UDP_AIBaseEvent
{
	GENERATED_BODY()

public:
	UDP_AIMoveEvent();

	virtual void OnBegin(bool bFirstTime) override;
	virtual void OnUpdate() override;
	virtual void OnEnd() override;
	virtual bool IsDone() override;

	UFUNCTION(BlueprintCallable)
	void SetDependencies(TArray<FVector> Path) { PatrolPath = Path; }

public:
	UPROPERTY(BlueprintReadOnly, Category="AI", meta=(AllowPrivateAccess="true"))
	bool bShouldMove{true};

	UPROPERTY(BlueprintReadOnly, Category="AI", meta=(AllowPrivateAccess="true"))
	FVector TargetLocation{};

	UPROPERTY(BlueprintReadOnly, Category="AI", meta=(AllowPrivateAccess="true"))
	TArray<FVector> PatrolPath{};
};
