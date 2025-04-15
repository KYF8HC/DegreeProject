#include "Characters/DP_PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameplayAbilities/DP_AbilitySystemComponent.h"
#include "GameplayAbilities/DP_AttributeSet.h"
#include "GUI/HUD/DP_PlayerHUD.h"
#include "Player/DP_PlayerController.h"


ADP_PlayerCharacter::ADP_PlayerCharacter()
{
	SetNetUpdateFrequency(100.0f);
	PrimaryActorTick.bCanEverTick = false;

	SpringArmComponentRef = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponentRef->SetupAttachment(RootComponent);

	CameraComponentRef = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponentRef->SetupAttachment(SpringArmComponentRef);

	AbilitySystemComponentRef = CreateDefaultSubobject<UDP_AbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponentRef->SetIsReplicated(true);
	AbilitySystemComponentRef->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSetRef = CreateDefaultSubobject<UDP_AttributeSet>(TEXT("AttributeSet"));
}

void ADP_PlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	PlayerControllerRef = Cast<ADP_PlayerController>(NewController);

	//Init for server
	InitAbilityActorInfo();
}

void ADP_PlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//Init for client
	PlayerControllerRef = Cast<ADP_PlayerController>(GetController());
	InitAbilityActorInfo();
}

void ADP_PlayerCharacter::Begin()
{
	
}


void ADP_PlayerCharacter::HandleMove(const FVector2D& InputAxisVector)
{
	const FRotator ControlRotation = GetControlRotation();
	const FRotator YawRotation(0, ControlRotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, InputAxisVector.Y);
	AddMovementInput(RightDirection, InputAxisVector.X);
}

void ADP_PlayerCharacter::HandleLook(const FVector2D& InputAxisVector)
{
	AddControllerYawInput(InputAxisVector.X);
	AddControllerPitchInput(InputAxisVector.Y);
}

void ADP_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ADP_PlayerCharacter::Death()
{
	//Reload level
	if (PlayerControllerRef)
	{
		PlayerControllerRef->RestartLevel();
	}
}


void ADP_PlayerCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponentRef->InitAbilityActorInfo(this, this);
	UE_LOG(LogTemp, Warning, TEXT("ADP_PlayerCharacter::InitAbilityActorInfo"));
	ADP_PlayerHUD* PlayerHUD = Cast<ADP_PlayerHUD>(PlayerControllerRef->GetHUD());
	PlayerHUD->InitOverlay(PlayerControllerRef, AbilitySystemComponentRef, AttributeSetRef);
}

