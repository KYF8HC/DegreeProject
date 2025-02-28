#include "Player/DP_PlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Characters/DP_PlayerCharacter.h"
#include "GUI/HUD/DP_PlayerHUD.h"
#include "Player/DP_PlayerState.h"

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

	SetCanReceiveInput(false);
}

void ADP_PlayerController::OnRep_Pawn()
{
	Super::OnRep_Pawn();
	SetupController(GetPawn());
}

void ADP_PlayerController::SetCanReceiveInput(bool bCanReceive)
{
	if (bCanReceive)
	{
		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);
	}
	else
	{
		FInputModeUIOnly InputMode;
		SetInputMode(InputMode);
	}

	SetShowMouseCursor(!bCanReceive);
	bCanReceiveInput = bCanReceive;
}

void ADP_PlayerController::OnBegin()
{
	OnBeginClient();
}

void ADP_PlayerController::OnBeginClient_Implementation()
{
	SetCanReceiveInput(true);
	ADP_PlayerHUD* PlayerHUD = Cast<ADP_PlayerHUD>(GetHUD());
	ADP_PlayerState* PlayerStateRef = Cast<ADP_PlayerState>(PlayerState);
	PlayerHUD->InitOverlay(this,
	                       PlayerStateRef,
	                       UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(PlayerStateRef),
	                       PlayerStateRef->GetAttributeSet());
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
	EnhancedInputComponentRef->BindAction(Shoot, ETriggerEvent::Triggered, this, &ADP_PlayerController::HandleShoot);
}

void ADP_PlayerController::HandleMove(const FInputActionValue& Value)
{
	if (!bCanReceiveInput)
		return;

	const FVector2D InputAxisVector = Value.Get<FVector2D>();
	PlayerCharacterRef->HandleMove(InputAxisVector);
}

void ADP_PlayerController::HandleLook(const FInputActionValue& Value)
{
	if (!bCanReceiveInput)
		return;

	const FVector2D InputAxisVector = Value.Get<FVector2D>();
	PlayerCharacterRef->HandleLook(InputAxisVector);
}

void ADP_PlayerController::HandleShoot()
{
	if (!bCanReceiveInput)
		return;

	PlayerCharacterRef->HandleShoot();
}
