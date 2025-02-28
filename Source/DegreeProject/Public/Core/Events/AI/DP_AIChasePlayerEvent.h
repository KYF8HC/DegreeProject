#pragma once

#include "CoreMinimal.h"
#include "Core/Events/AI/DP_AIBaseEvent.h"
#include "DP_AIChasePlayerEvent.generated.h"

UCLASS(BlueprintType, Blueprintable)
class DEGREEPROJECT_API UDP_AIChasePlayerEvent : public UDP_AIBaseEvent
{
	GENERATED_BODY()

public:
	UDP_AIChasePlayerEvent();

	virtual void OnBegin(bool bFirstTime) override;
	virtual void OnUpdate() override;
	virtual void OnEnd() override;
	virtual bool IsDone() override;

	UFUNCTION(BlueprintCallable)
	void SetTarget(AActor* TargetActor) { TargetActorRef = TargetActor; }

private:
	bool bShouldChase{true};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI", meta=(AllowPrivateAccess="true"))
	float AttackRange{100.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Events", meta=(AllowPrivateAccess="true"))
	TSubclassOf<UDP_AIBaseEvent> AttackEventClass{};

	UPROPERTY()
	TObjectPtr<AActor> TargetActorRef{};
};
