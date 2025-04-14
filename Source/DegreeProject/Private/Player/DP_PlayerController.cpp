#include "Player/DP_PlayerController.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Characters/DP_PlayerCharacter.h"
#include "Core/DP_GameMode.h"
#include "GUI/Widgets/DP_DamageTextComponent.h"
#include "Kismet/GameplayStatics.h"

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

void ADP_PlayerController::OnBegin(bool bFirstTime)
{
	OnBeginClient();
	PlayerCharacterRef->Begin();
}

void ADP_PlayerController::OnBeginClient_Implementation()
{
	SetCanReceiveInput(true);
}

void ADP_PlayerController::ShowDamageNumber_Implementation(float DamageAmount, ACharacter* TargetCharacter,
                                                           bool bIsDodgedHit, bool bIsCriticalHit)
{
	if (IsValid(TargetCharacter) && DamageTextComponentClass)
	{
		UDP_DamageTextComponent* DamageTextCompRef = NewObject<UDP_DamageTextComponent>(
			TargetCharacter, DamageTextComponentClass);
		DamageTextCompRef->RegisterComponent();
		DamageTextCompRef->AttachToComponent(TargetCharacter->GetRootComponent(),
		                                     FAttachmentTransformRules::KeepRelativeTransform);
		DamageTextCompRef->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageTextCompRef->SetDamageText(DamageAmount, bIsDodgedHit, bIsCriticalHit);
	}
}

void ADP_PlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	Cast<ADP_GameMode>(UGameplayStatics::GetGameMode(this))->OnBeginDelegate.AddDynamic(this, &ADP_PlayerController::OnBegin);

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
}
