#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DP_PlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
class ADP_PlayerCharacter;
class UInputMappingContext;
class UDP_DamageTextComponent;
class UEnhancedInputLocalPlayerSubsystem;

UCLASS(Abstract)
class DEGREEPROJECT_API ADP_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void OnRep_Pawn() override;

	UFUNCTION(BlueprintCallable)
	void SetCanReceiveInput(bool bCanReceive);

	UFUNCTION()
	void OnBegin(bool bFirstTime);

	UFUNCTION(CLient, Reliable)
	void OnBeginClient();

	UFUNCTION(Client, Reliable)
	void ShowDamageNumber(float DamageAmount, ACharacter* TargetCharacter, bool bIsDodgedHit, bool bIsCriticalHit);

protected:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void SetupInputComponent() override;
	void SetupController(APawn* aPawn);

private:
	bool bCanReceiveInput{false};

#pragma region Input Actions
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> MappingContext{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Move{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Look{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Shoot{};

#pragma endregion

#pragma region System References
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ADP_PlayerCharacter> PlayerCharacterRef{};

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponentRef{};

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSubsystemRef{};
#pragma endregion

	UPROPERTY(EditAnywhere)
	TSubclassOf<UDP_DamageTextComponent> DamageTextComponentClass{};
	
	void BindInputActions();
	void HandleMove(const FInputActionValue& Value);
	void HandleLook(const FInputActionValue& Value);
	void HandleShoot();

};
