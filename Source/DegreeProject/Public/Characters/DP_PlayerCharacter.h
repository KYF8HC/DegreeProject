#pragma once

#include "CoreMinimal.h"
#include "DP_BaseCharacter.h"
#include "DP_PlayerCharacter.generated.h"

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
	
	
	void HandleMove(const FVector2D& InputAxisVector);
	void HandleLook(const FVector2D& InputAxisVector);
	
protected:
	virtual void BeginPlay() override;


private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerCamera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArmComponentRef{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerCamera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponentRef{};

	void InitAbilityActorInfo();
};
