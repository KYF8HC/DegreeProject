﻿#include "GameplayAbilities/Abilities/DP_DamageGameplayAbility.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "FDP_GameplayTags.h"
#include "Actors/DP_AbilityActor.h"
#include "GameplayAbilities/DP_AbilitySystemComponent.h"
#include "Interaction/CombatInterface.h"

void UDP_DamageGameplayAbility::CauseDamage(AActor* CombatTarget)
{
	FGameplayEffectSpecHandle DamageSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass, 1.0f);
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
		
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(GetAvatarActorFromActorInfo()->GetActorLocation());
		SpawnTransform.SetRotation(GetAvatarActorFromActorInfo()->GetActorForwardVector().ToOrientationQuat());

		ADP_AbilityActor* AbilityActor = GetWorld()->SpawnActorDeferred<ADP_AbilityActor>(
			AbilityActorClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn
		);


		UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(
			GetAvatarActorFromActorInfo());

		FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
		EffectContextHandle.SetAbility(this);
		EffectContextHandle.AddSourceObject(AbilityActor);

		TArray<TWeakObjectPtr<AActor>> Actors;
		Actors.Add(AbilityActor);
		FHitResult HitResult;
		EffectContextHandle.AddHitResult(HitResult);

		const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(
			DamageEffectClass, GetAbilityLevel(), EffectContextHandle);

		FDP_GameplayTags GameplayTags = FDP_GameplayTags::Get();

		for (auto& Pair : DamageTypes)
		{
			const float ScaledDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
			UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, ScaledDamage);
		}

		AbilityActor->SetInstigator(GetAvatarActorFromActorInfo()->GetInstigator());
		AbilityActor->DamageEffectSpecHandle = SpecHandle;
		AbilityActor->SetMaxAmmo(MaxAmmo);
		AbilityActor->InitializeAbilityActor();
		AbilityActor->OnOutOfAmmo.AddDynamic(this, &UDP_DamageGameplayAbility::OnOutOfAmmo);
		
		AbilityActor->FinishSpawning(SpawnTransform);
		AbilityActor->AttachToActor(GetAvatarActorFromActorInfo(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	}
}
