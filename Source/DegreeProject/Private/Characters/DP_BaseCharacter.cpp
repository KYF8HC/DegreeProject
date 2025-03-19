#include "Characters/DP_BaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "DegreeProject/DegreeProject.h"
#include "GameplayAbilities/DP_AbilitySystemLibrary.h"
#include "GameplayAbilities/DP_AttributeSet.h"

ADP_BaseCharacter::ADP_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
}

UAbilitySystemComponent* ADP_BaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponentRef;
}

void ADP_BaseCharacter::Death()
{
	Disolve();
}

void ADP_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	UDP_AbilitySystemLibrary::GiveStartupAbilities(this, CharacterClass, AbilitySystemComponentRef);
	UDP_AbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponentRef);
}

void ADP_BaseCharacter::Disolve()
{
	if (IsValid(DissolveMaterialInstanceRef))
	{
		UMaterialInstance* DynamicMaterialIns = UMaterialInstanceDynamic::Create(DissolveMaterialInstanceRef, this);
		GetMesh()->SetMaterial(0, DynamicMaterialIns);
		StartDisolveTimeline(DynamicMaterialIns);
	}
}
