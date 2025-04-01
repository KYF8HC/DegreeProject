#pragma once

#include "CoreMinimal.h"
#include "DP_EffectActor.h"
#include "DP_DamageEffectActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEffectOutOfAmmo);

UCLASS()
class DEGREEPROJECT_API ADP_DamageEffectActor : public ADP_EffectActor
{
	GENERATED_BODY()

public:
	ADP_DamageEffectActor();
	
	UPROPERTY(BlueprintReadWrite, Category = "Damage", meta = (ExposeOnSpawn = "true"))
	FGameplayEffectSpecHandle DamageEffectSpecHandle{};

	UPROPERTY(BlueprintAssignable, Category = "Weapon Attributes")
	FOnEffectOutOfAmmo OnEffectOutOfAmmo;
	
	virtual void Tick(float DeltaSeconds) override;

	void InitializeAbilityActor();
	void SetMaxAmmo(float NewMaxAmmo) { MaxAmmo = NewMaxAmmo; }
	float GetAmmo() const { return Ammo; }
protected:

	UPROPERTY(BlueprintReadOnly, Category = "Weapon Attributes")
	float Ammo{};

	UPROPERTY(BlueprintReadOnly, Category = "Weapon Attributes")
	float MaxAmmo{};

	bool bIsInitialized{ false };
	
	virtual bool OnOverlap(AActor* TargetActor) override;
	virtual bool OnEndOverlap(AActor* TargetActor) override;

};
