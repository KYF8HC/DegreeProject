#include "Characters/DP_BaseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DegreeProject/DegreeProject.h"
#include "GameplayAbilities/DP_AbilitySystemLibrary.h"

ADP_BaseCharacter::ADP_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);

	WeaponMeshRef = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	WeaponMeshRef->SetupAttachment(GetMesh(), TEXT("Staff_Socket"));
}

UAbilitySystemComponent* ADP_BaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponentRef;
}

FVector ADP_BaseCharacter::GetCombatSocketLocation()
{
	return FVector(); //WeaponStaticMesh->GetComponentLocation(); 
}

void ADP_BaseCharacter::Death()
{
	Destroy();
}

void ADP_BaseCharacter::SetCharacterLevel(const int32 NewLevel)
{
	Level = NewLevel;
	OnLevelChanged.Broadcast(Level);
}

void ADP_BaseCharacter::AddToLevel(const int32 Amount)
{
	Level += Amount;
	if (Level < 1)
		Level = 1;

	UE_LOG(LogTemp, Display, TEXT("Level = %d"), Level);
	
	OnLevelChanged.Broadcast(Level);
}

void ADP_BaseCharacter::SetExperiencePoints(const int32 NewExperiencePoints)
{
	ExperiencePoints = NewExperiencePoints;
	OnExperiencePointsChanged.Broadcast(ExperiencePoints);
}

void ADP_BaseCharacter::AddToExperiencePoints(const int32 Amount)
{
	ExperiencePoints += Amount;
	if (ExperiencePoints < 0)
		ExperiencePoints = 0;
	
	OnExperiencePointsChanged.Broadcast(ExperiencePoints);	
}

ECharacterClass ADP_BaseCharacter::GetCharacterClass_Implementation()
{
	return CharacterClass;
}

void ADP_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	UDP_AbilitySystemLibrary::GiveStartupAbilities(this, CharacterClass, AbilitySystemComponentRef);
	UDP_AbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponentRef);
}
