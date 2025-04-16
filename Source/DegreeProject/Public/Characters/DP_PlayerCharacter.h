#pragma once

#include "CoreMinimal.h"
#include "DP_BaseCharacter.h"
#include "GameplayTagContainer.h"
#include "Interaction/DP_PlayerInterface.h"
#include "DP_PlayerCharacter.generated.h"

class UDP_LevelUpInfo;
class UDP_GameplayAbility;
class ADP_PlayerController;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class DEGREEPROJECT_API ADP_PlayerCharacter : public ADP_BaseCharacter, public IDP_PlayerInterface
{
	GENERATED_BODY()

public:
	ADP_PlayerCharacter();

	#pragma region Ability System
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GAS | Level")
	TObjectPtr<UDP_LevelUpInfo> LevelUpInfo{};
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
	#pragma endregion

	virtual void AddToPlayerExperience_Implementation(int32 ExperienceAmount) override;

	
	void Begin();
	void HandleMove(const FVector2D& InputAxisVector);
	void HandleLook(const FVector2D& InputAxisVector);
	virtual bool IsEnemy() override { return false; }
	
protected:
	virtual void BeginPlay() override;
	virtual void Death() override;
private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "GAS", meta = (AllowPrivateAccess = "true"))
	FGameplayTag StartWeaponTag{};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerCamera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArmComponentRef{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerCamera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponentRef{};
	
	UPROPERTY()
	TObjectPtr<ADP_PlayerController> PlayerControllerRef{};
	
	void InitAbilityActorInfo();

};
