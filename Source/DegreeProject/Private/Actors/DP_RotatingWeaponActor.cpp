#include "Actors/DP_RotatingWeaponActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "DegreeProject/DegreeProject.h"
#include "GameFramework/RotatingMovementComponent.h"

ADP_RotatingWeaponActor::ADP_RotatingWeaponActor()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	
	SceneComponentRef = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponentRef);

	CapsuleComponentRef = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	CapsuleComponentRef->SetupAttachment(RootComponent);
	CapsuleComponentRef->SetCollisionObjectType(ECC_Projectile);
	CapsuleComponentRef->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CapsuleComponentRef->SetCollisionResponseToAllChannels(ECR_Ignore);
	CapsuleComponentRef->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CapsuleComponentRef->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	CapsuleComponentRef->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);

	RotatingMovementComponentRef = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComponent"));
	RotatingMovementComponentRef->RotationRate = FRotator(0.0f, 0.0f, 180.0f);
	RotatingMovementComponentRef->UpdatedComponent = RootComponent;
	
	
}

void ADP_RotatingWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(GetInstigator()->GetActorLocation());
}

void ADP_RotatingWeaponActor::OnCapsuleComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (HasAuthority())
	{
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
		}
	}
}

void ADP_RotatingWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	CapsuleComponentRef->OnComponentBeginOverlap.AddDynamic(this, &ADP_RotatingWeaponActor::OnCapsuleComponentOverlap);
}

