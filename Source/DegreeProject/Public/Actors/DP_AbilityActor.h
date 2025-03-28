#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "DP_AbilityActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOutOfAmmo);

UCLASS()
class DEGREEPROJECT_API ADP_AbilityActor : public AActor
{
	GENERATED_BODY()

public:
	ADP_AbilityActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USceneComponent> SceneComponentRef{};
	
	UPROPERTY(BlueprintReadWrite, Category = "Damage", meta = (ExposeOnSpawn = "true"))
	FGameplayEffectSpecHandle DamageEffectSpecHandle{};

	UPROPERTY(BlueprintAssignable, Category = "Weapon Attributes")
	FOnOutOfAmmo OnOutOfAmmo;

	void InitializeAbilityActor();
	void SetMaxAmmo(float NewMaxAmmo) { MaxAmmo = NewMaxAmmo; }
	float GetAmmo() const { return Ammo; }
protected:

	UPROPERTY(BlueprintReadOnly, Category = "Weapon Attributes")
	float Ammo{};

	UPROPERTY(BlueprintReadOnly, Category = "Weapon Attributes")
	float MaxAmmo{};

	bool bIsInitialized{ false };
	
};
