#pragma once

#include "CoreMinimal.h"
#include "DP_AbilityActor.h"
#include "DP_RotatingWeaponActor.generated.h"

class UCapsuleComponent;
class URotatingMovementComponent;

UCLASS()
class DEGREEPROJECT_API ADP_RotatingWeaponActor : public ADP_AbilityActor
{
	GENERATED_BODY()

public:
	ADP_RotatingWeaponActor();
	
	virtual void Tick(float DeltaTime) override;
protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	TObjectPtr<URotatingMovementComponent> RotatingMovementComponentRef{};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> CapsuleComponentRef{};

	UFUNCTION(BlueprintCallable)
	void OnCapsuleComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                               int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void BeginPlay() override;
};
