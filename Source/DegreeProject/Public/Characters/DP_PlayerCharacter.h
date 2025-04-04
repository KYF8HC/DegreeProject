﻿#pragma once

#include "CoreMinimal.h"
#include "DP_BaseCharacter.h"
#include "GameplayTagContainer.h"
#include "DP_PlayerCharacter.generated.h"

class UDP_GameplayAbility;
class ADP_PlayerController;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class DEGREEPROJECT_API ADP_PlayerCharacter : public ADP_BaseCharacter
{
	GENERATED_BODY()

public:
	ADP_PlayerCharacter();

	#pragma region Ability System
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
	#pragma endregion

	void HandleCooldownTagChanged(FGameplayTag GameplayTag, int Count);
	void Begin();
	
	void HandleMove(const FVector2D& InputAxisVector);
	void HandleLook(const FVector2D& InputAxisVector);
	void InitOverlay();
	virtual bool IsEnemy() override { return false; }
	
protected:
	virtual void BeginPlay() override;
	virtual void Death() override;
private:

	//TODO: TEMP!!!!!!!!!!
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "GAS", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UGameplayAbility>> Abilities{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "GAS", meta = (AllowPrivateAccess = "true"))
	FGameplayTagContainer CooldownTags{};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerCamera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArmComponentRef{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerCamera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponentRef{};
	
	UPROPERTY()
	TObjectPtr<ADP_PlayerController> PlayerControllerRef{};
	
	void InitAbilityActorInfo();
};
