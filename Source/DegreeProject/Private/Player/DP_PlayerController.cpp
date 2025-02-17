#include "Player/DP_PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Characters/DP_PlayerCharacter.h"

void ADP_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	EnhancedInputComponentRef = CastChecked<UEnhancedInputComponent>(InputComponent);
}

void ADP_PlayerController::SetupController(APawn* aPawn)
{
	PlayerCharacterRef = CastChecked<ADP_PlayerCharacter>(aPawn);
	checkf(PlayerCharacterRef, TEXT("ADP_PlayerController::OnPossess: PlayerController can only possess a Character"));

	InputSubsystemRef = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (InputSubsystemRef)
	{
		InputSubsystemRef->AddMappingContext(MappingContext, 0);
	}
	BindInputActions();
}

void ADP_PlayerController::OnRep_Pawn()
{
	Super::OnRep_Pawn();
	SetupController(GetPawn());
}

void ADP_PlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	if (IsLocalController())
	{
		SetupController(aPawn);
	}
}

void ADP_PlayerController::BindInputActions()
{
	EnhancedInputComponentRef->BindAction(Move, ETriggerEvent::Triggered, this, &ADP_PlayerController::HandleMove);
	EnhancedInputComponentRef->BindAction(Look, ETriggerEvent::Triggered, this, &ADP_PlayerController::HandleLook);
}

void ADP_PlayerController::HandleMove(const FInputActionValue& Value)
{
	const FVector2D InputAxisVector = Value.Get<FVector2D>();
	PlayerCharacterRef->HandleMove(InputAxisVector);
}

void ADP_PlayerController::HandleLook(const FInputActionValue& Value)
{
	const FVector2D InputAxisVector = Value.Get<FVector2D>();
	PlayerCharacterRef->HandleLook(InputAxisVector);
}
