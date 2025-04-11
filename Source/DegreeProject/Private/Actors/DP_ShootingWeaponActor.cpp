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

		ADP_Projectile* Projectile = GetWorld()->SpawnActorDeferred<ADP_Projectile>(
			ProjectileClass, SpawnPoint, this);
		Projectile->DamageEffectSpecHandle = DamageEffectSpecHandle;
		Projectile->FinishSpawning(SpawnPoint);
	}

	Ammo -= ProjectileSpawnPoints.Num();
}
