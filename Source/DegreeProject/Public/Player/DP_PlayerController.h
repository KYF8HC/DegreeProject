﻿#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DP_PlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class UEnhancedInputLocalPlayerSubsystem;
class ADP_PlayerCharacter;

UCLASS(Abstract)
class DEGREEPROJECT_API ADP_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:

	virtual void OnRep_Pawn() override;
	
protected:
	
	virtual void OnPossess(APawn* aPawn) override;
	virtual void SetupInputComponent() override;
	void SetupController(APawn* aPawn);

private:

#pragma region Input Actions
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> MappingContext{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Move{};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Look{};

#pragma endregion

#pragma region System References	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ADP_PlayerCharacter> PlayerCharacterRef{};

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponentRef{};

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSubsystemRef{};
#pragma endregion

	void BindInputActions();
	void HandleMove(const FInputActionValue& Value);
	void HandleLook(const FInputActionValue& Value);

};
