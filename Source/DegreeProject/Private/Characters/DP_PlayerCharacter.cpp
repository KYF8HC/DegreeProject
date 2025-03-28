#include "Characters/DP_PlayerCharacter.h"

#include "FDP_GameplayTags.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameplayAbilities/DP_AbilitySystemComponent.h"
#include "GameplayAbilities/DP_AttributeSet.h"
#include "GUI/HUD/DP_PlayerHUD.h"
#include "Player/DP_PlayerController.h"
#include "Player/DP_PlayerState.h"


ADP_PlayerCharacter::ADP_PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	SpringArmComponentRef = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponentRef->SetupAttachment(RootComponent);

	CameraComponentRef = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponentRef->SetupAttachment(SpringArmComponentRef);
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

void ADP_PlayerCharacter::HandleCooldownTagChanged(FGameplayTag GameplayTag, int Count)
{
	if (Count > 0)
		return;

	for (const TTuple<FGameplayTag, FGameplayTag>& Pair : FDP_GameplayTags::Get().CooldownsToAbilities)
	{
		const FGameplayTag InCooldownTag = Pair.Key;
		const FGameplayTag InAbilityTag = Pair.Value;

		if (GameplayTag == InCooldownTag)
		{
			UE_LOG(LogTemp, Log, TEXT("Ability %s is off cooldown"), *InAbilityTag.ToString());
			FGameplayTagContainer TagContainer;
			TagContainer.AddTag(InAbilityTag);
			AbilitySystemComponentRef->TryActivateAbilitiesByTag(TagContainer);
		}
	}
}

void ADP_PlayerCharacter::Begin()
{
	for (auto AbilityClass : Abilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, GetPlayerLevel());
		FGameplayAbilitySpecHandle AbilitySpecHandle = AbilitySystemComponentRef->GiveAbility(AbilitySpec);
		AbilitySystemComponentRef->TryActivateAbility(AbilitySpecHandle);
	}

	for (FGameplayTag CooldownTag : CooldownTags)
	{
		AbilitySystemComponentRef->RegisterGameplayTagEvent(CooldownTag, EGameplayTagEventType::NewOrRemoved).
		                           AddUObject(
			                           this, &ADP_PlayerCharacter::HandleCooldownTagChanged);
	}
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

void ADP_PlayerCharacter::InitOverlay()
{
	if (PlayerControllerRef)
	{
		ADP_PlayerHUD* HUD = Cast<ADP_PlayerHUD>(PlayerControllerRef->GetHUD());
		if (HUD)
		{
			HUD->InitOverlay(PlayerControllerRef, GetPlayerState(), AbilitySystemComponentRef, AttributeSetRef);
		}
	}
}

void ADP_PlayerCharacter::InitAbilityActorInfo()
{
	auto PS = Cast<ADP_PlayerState>(GetPlayerState());
	AbilitySystemComponentRef = CastChecked<UDP_AbilitySystemComponent>(PS->GetAbilitySystemComponent());
	AttributeSetRef = CastChecked<UDP_AttributeSet>(PS->GetAttributeSet());

	AbilitySystemComponentRef->InitAbilityActorInfo(PS, this);
}
