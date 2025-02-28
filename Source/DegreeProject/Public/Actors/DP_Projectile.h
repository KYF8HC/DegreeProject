#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "DP_Projectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class DEGREEPROJECT_API ADP_Projectile : public AActor
{
	GENERATED_BODY()

public:
	ADP_Projectile();

	UPROPERTY(BlueprintReadWrite, Category = "Damage", meta = (ExposeOnSpawn = "true"))
	FGameplayEffectSpecHandle DamageEffectSpecHandle{};
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                     int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	float LifeSpan{10.0f};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> SphereComponentRef{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponentRef{};
};
