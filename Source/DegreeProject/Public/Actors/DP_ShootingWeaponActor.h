#pragma once

#include "CoreMinimal.h"
#include "DP_AbilityActor.h"
#include "DP_ShootingWeaponActor.generated.h"

class ADP_Projectile;

UCLASS()
class DEGREEPROJECT_API ADP_ShootingWeaponActor : public ADP_AbilityActor
{
	GENERATED_BODY()

public:
	ADP_ShootingWeaponActor();

	virtual void Tick(float DeltaTime) override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Attributes")
	float FireRate{1.0f};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Attributes")
	TArray<FTransform> ProjectileSpawnPoints{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Attributes")
	TSubclassOf<ADP_Projectile> ProjectileClass{};

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void SetProjectileSpawnPoints();
};
