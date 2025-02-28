#include "Actors/DP_Projectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/SphereComponent.h"
#include "DegreeProject/DegreeProject.h"
#include "GameFramework/ProjectileMovementComponent.h"


ADP_Projectile::ADP_Projectile()
{
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates(true);

	SphereComponentRef = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(SphereComponentRef);
	SphereComponentRef->SetCollisionObjectType(ECC_Projectile);
	SphereComponentRef->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponentRef->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComponentRef->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComponentRef->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	SphereComponentRef->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);

	ProjectileMovementComponentRef = CreateDefaultSubobject<UProjectileMovementComponent>(
		TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponentRef->InitialSpeed = 700.0f;
	ProjectileMovementComponentRef->MaxSpeed = 700.0f;
	ProjectileMovementComponentRef->ProjectileGravityScale = 0.0f;
}

void ADP_Projectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeSpan);
	SphereComponentRef->OnComponentBeginOverlap.AddDynamic(this, &ADP_Projectile::OnSphereOverlap);
}

void ADP_Projectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                     const FHitResult& SweepResult)
{
	if (HasAuthority())
	{
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
		}
		Destroy();
	}
}
