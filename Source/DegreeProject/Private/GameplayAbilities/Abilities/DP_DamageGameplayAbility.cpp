#include "GameplayAbilities/Abilities/DP_DamageGameplayAbility.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "FDP_GameplayTags.h"
#include "Actors/DP_AbilityActor.h"
#include "Actors/DP_DamageEffectActor.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "GameplayAbilities/DP_AbilitySystemComponent.h"
#include "Interaction/CombatInterface.h"

void UDP_DamageGameplayAbility::CauseDamage(AActor* CombatTarget)
{
	FGameplayEffectSpecHandle DamageSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass, GetAbilityLevel());
	for (TTuple<FGameplayTag, FScalableFloat> Pair : DamageTypes)
	{
		const float ScaleDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageSpecHandle, Pair.Key, ScaleDamage);
	}

	UDP_AbilitySystemComponent* AbilitySystemComponent = Cast<UDP_AbilitySystemComponent>(
		GetAbilitySystemComponentFromActorInfo());

	AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(
		*DamageSpecHandle.Data.Get(),
		UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(CombatTarget));
}


void UDP_DamageGameplayAbility::InitializeEffectSpecHandle(AActor* NewActor, FGameplayEffectSpecHandle& SpecHandle)
{
	UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(
		GetAvatarActorFromActorInfo());

	FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
	EffectContextHandle.SetAbility(this);
	EffectContextHandle.AddSourceObject(NewActor);

	SpecHandle = SourceASC->MakeOutgoingSpec(
		DamageEffectClass, GetAbilityLevel(), EffectContextHandle);

	FDP_GameplayTags GameplayTags = FDP_GameplayTags::Get();

	for (auto& Pair : DamageTypes)
	{
		const float ScaledDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, ScaledDamage);
	}
}

void UDP_DamageGameplayAbility::SetupAbilityActor(AActor* NewActor, const FGameplayEffectSpecHandle SpecHandle)
{
	if (ADP_AbilityActor* AbilityActor = Cast<ADP_AbilityActor>(NewActor))
	{
		AbilityActor->SetInstigator(GetAvatarActorFromActorInfo()->GetInstigator());
		AbilityActor->DamageEffectSpecHandle = SpecHandle;
		AbilityActor->SetMaxAmmo(MaxAmmo);
		AbilityActor->InitializeAbilityActor();
		AbilityActor->OnOutOfAmmo.AddDynamic(this, &UDP_DamageGameplayAbility::OnOutOfAmmo);
	}

	if (ADP_DamageEffectActor* DamageEffectActor = Cast<ADP_DamageEffectActor>(NewActor))
	{
		DamageEffectActor->DamageEffectSpecHandle = SpecHandle;
		DamageEffectActor->SetMaxAmmo(MaxAmmo);
		DamageEffectActor->InitializeAbilityActor();
		DamageEffectActor->OnEffectOutOfAmmo.AddDynamic(this, &UDP_DamageGameplayAbility::OnOutOfAmmo);
	}
}

void UDP_DamageGameplayAbility::SpawnAbilityActor(const FTransform& SpawnTransform)
{
	AActor* NewActor = GetWorld()->SpawnActorDeferred<AActor>(
		AbilityActorClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);


	FGameplayEffectSpecHandle SpecHandle;
	InitializeEffectSpecHandle(NewActor, SpecHandle);
	SetupAbilityActor(NewActor, SpecHandle);

	NewActor->FinishSpawning(SpawnTransform);
	if (bShouldSpawnOnActor)
		NewActor->AttachToActor(GetAvatarActorFromActorInfo(), FAttachmentTransformRules::SnapToTargetIncludingScale);
}

void UDP_DamageGameplayAbility::StartAbilityActorSpawn()
{
	if (bShouldSpawnOnActor)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(GetAvatarActorFromActorInfo()->GetActorLocation());
		SpawnTransform.SetRotation(GetAvatarActorFromActorInfo()->GetActorForwardVector().ToOrientationQuat());
		SpawnAbilityActor(SpawnTransform);
		return;
	}

	UEnvQueryInstanceBlueprintWrapper* QueryInstance
		= UEnvQueryManager::RunEQSQuery(this, SpawnQuery, this,
		                                EEnvQueryRunMode::RandomBest5Pct, nullptr);

	if (ensureMsgf(QueryInstance, TEXT("UDP_DamageGameplayAbility::StartAbilityActorSpawn: QueryInstance is nullptr")))
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &UDP_DamageGameplayAbility::OnSpawnQueryFinished);
}

void UDP_DamageGameplayAbility::OnSpawnQueryFinished(UEnvQueryInstanceBlueprintWrapper* QueryInstance,
                                                     EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("UDP_DamageGameplayAbility::OnSpawnQueryFinished: QueryStatus is not Success"));
		return;
	}

	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();
	if (Locations.Num() <= 0)
	{
		return;
	}

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(Locations[0]);

	UE_LOG(LogTemp, Log, TEXT("Locations[0]: %s"), *Locations[0].ToString());

	SpawnTransform.SetRotation(FQuat::Identity);
	SpawnAbilityActor(SpawnTransform);
}

void UDP_DamageGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                const FGameplayAbilityActorInfo* ActorInfo,
                                                const FGameplayAbilityActivationInfo ActivationInfo,
                                                const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);


	const bool bIsServer = HasAuthority(&ActivationInfo);
	if (!bIsServer) return;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());

	//TODO: TEMPORARY
	if (CombatInterface->IsEnemy())
		return;


	if (CombatInterface)
	{
		StartAbilityActorSpawn();
	}
}
