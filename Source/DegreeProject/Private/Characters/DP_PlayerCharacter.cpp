﻿#include "Characters/DP_PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Data/DP_LevelUpInfo.h"
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

	WeaponMeshRef = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	WeaponMeshRef->SetupAttachment(GetMesh(), TEXT("Staff_Socket"));
	
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

bool ADP_PlayerCharacter::CanLevelUp(int32 InExperiencePoints)
{
	return LevelUpInfo->GetLevelBasedOnExp(InExperiencePoints) > Level;
}

void ADP_PlayerCharacter::GrantWeaponTag_Implementation(FGameplayTag WeaponTag)
{
	if (WeaponTag.IsValid())
		OwnedWeapons.AddTag(WeaponTag);
}

void ADP_PlayerCharacter::AddToPlayerExperience_Implementation(int32 ExperienceAmount)
{
	const int32 TempExperience = ExperiencePoints + ExperienceAmount;

	while (CanLevelUp(TempExperience))
	{
		UE_LOG(LogTemp, Display, TEXT("Level: %d, TempExperience: %d"), Level, TempExperience);
		AddToLevel(1);
	}

	AddToExperiencePoints(ExperienceAmount);
}

void ADP_PlayerCharacter::LevelUp_Implementation()
{
}

int32 ADP_PlayerCharacter::GetLevelBasedOnExp_Implementation(int32 InExperiencePoints)
{
	return LevelUpInfo->GetLevelBasedOnExp(InExperiencePoints);
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

	CharacterClass = ECharacterClass::Mage;
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
	PlayerHUD->InitOverlay(PlayerControllerRef, this, AbilitySystemComponentRef, AttributeSetRef);
}
