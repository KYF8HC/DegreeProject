#pragma once

#include "CoreMinimal.h"
#include "Core/Events/AI/DP_AIBaseEvent.h"
#include "DP_ChasePlayerEvent.generated.h"

UCLASS(BlueprintType, Blueprintable)
class DEGREEPROJECT_API UDP_ChasePlayerEvent : public UDP_AIBaseEvent
{
	GENERATED_BODY()

public:
	UDP_ChasePlayerEvent();

	virtual void OnBegin(bool bFirstTime) override;
	virtual void OnUpdate() override;
	virtual void OnEnd() override;
	virtual bool IsDone() override;

	UFUNCTION(BlueprintCallable)
	void SetTarget(AActor* Target) { TargetRef = Target; }

private:
	bool bShouldChase{true};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI", meta=(AllowPrivateAccess="true"))
	float AttackRange{100.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Events", meta=(AllowPrivateAccess="true"))
	TSubclassOf<UDP_AIBaseEvent> AttackEventClass{};

	UPROPERTY()
	TObjectPtr<AActor> TargetRef{};
};
