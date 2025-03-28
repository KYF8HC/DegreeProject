#include "Actors/DP_ShootingWeaponActor.h"

#include "Actors/DP_Projectile.h"


ADP_ShootingWeaponActor::ADP_ShootingWeaponActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADP_ShootingWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.TickInterval = FireRate;
}

void ADP_ShootingWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetProjectileSpawnPoints();
	for (FTransform& SpawnPoint : ProjectileSpawnPoints)
	{
		//FTransform WorldTransform = GetActorTransform() * SpawnPoint;
		FVector SpawnLocation = SpawnPoint.GetLocation();
		FRotator SpawnRotation = SpawnPoint.Rotator();
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;

		ADP_Projectile* Projectile = GetWorld()->SpawnActor<ADP_Projectile>(
			ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
		Projectile->DamageEffectSpecHandle = DamageEffectSpecHandle;
	}

	Ammo -= ProjectileSpawnPoints.Num();
}
