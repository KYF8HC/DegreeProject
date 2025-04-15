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
	PrimaryActorTick.bCanEverTick = true;

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

void ADP_PlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	TArray<FGameplayAbilitySpecHandle> AbilityHandles;
	AbilitySystemComponentRef->GetAllAbilities(AbilityHandles);

	for (const FGameplayAbilitySpecHandle& AbilityHandle : AbilityHandles)
	{
		FGameplayAbilitySpec* Spec = AbilitySystemComponentRef->FindAbilitySpecFromHandle(AbilityHandle);
		if (Spec && Spec->Ability)
		{
			UGameplayAbility* Ability = Spec->Ability;

			// Option 1: Get tags from the Ability directly
			const FGameplayTagContainer& AbilityTags = Ability->AbilityTags;

			// Option 2: Get Activation Owned Tags (if that's what you want)
			// const FGameplayTagContainer& ActivationTags = Spec->DynamicAbilityTags;

			// Debug: Print or log the tags
			for (const FGameplayTag& Tag : AbilityTags)
			{
				UE_LOG(LogTemp, Log, TEXT("Ability Tag: %s"), *Tag.ToString());
			}
		}
	}
}

