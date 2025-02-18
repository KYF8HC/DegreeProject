#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayEffect.h"
#include "GameFramework/Actor.h"
#include "DP_EffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	RemoveOnEndOverlap,
	DoNotRemove
};

UENUM(BlueprintType)
enum class EEffectDurationType : uint8
{
	Instant,
	HasDuration,
	Infinite
};

USTRUCT(BlueprintType)
struct FGameplayEffectData
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	EEffectDurationType DurationType{EEffectDurationType::Instant};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Applied Effects")
	TSubclassOf<UGameplayEffect> GameplayEffectClassRef{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	EEffectApplicationPolicy ApplicationPolicy{EEffectApplicationPolicy::DoNotApply};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	EEffectRemovalPolicy RemovalPolicy{EEffectRemovalPolicy::DoNotRemove};
};

USTRUCT(BlueprintType)
struct FOverlappingActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	AActor* OverlappingActorRef{};

	UPROPERTY(VisibleAnywhere)
	bool bIsEffectApplied{false};

	FDelegateHandle OnAnyEffectRemovedHandle{};

	bool operator==(const FOverlappingActor& Other) const
	{
		return OverlappingActorRef == Other.OverlappingActorRef;
	}
};

UCLASS()
class DEGREEPROJECT_API ADP_EffectActor : public AActor
{
	GENERATED_BODY()

public:
	ADP_EffectActor();

protected:
	
	UPROPERTY(VisibleAnywhere)
	TArray<FOverlappingActor> OverlappingActors{};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Applied Effects")
	FGameplayEffectData GameplayEffectRef{};

	UPROPERTY(VisibleAnywhere)
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles{};

	UFUNCTION(BlueprintCallable)
	bool ApplyEffectToTarget(AActor* TargetActor, FGameplayEffectData GameplayEffect);

	void RemoveEffectFromTarget(AActor* TargetActor);

	UFUNCTION()
	void OnAnyEffectRemoved(const FActiveGameplayEffect& ActiveGameplayEffect);
	
	
	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);
};
