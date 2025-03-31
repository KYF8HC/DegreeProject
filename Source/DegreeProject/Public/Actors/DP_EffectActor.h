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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Overlapping Actor")
	AActor* OverlappingActorRef{};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Overlapping Actor")
	bool bIsEffectApplied{false};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Overlapping Actor")
	AActor* VisualEffectActorRef{};

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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Overlapping Actors")
	TArray<FOverlappingActor> OverlappingActors{};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Active Effects")
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect Properties")
	bool bDestroyOnEffectApplication{false};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect Properties")
	bool bApplyEffectToEnemies{false};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect Properties")
	bool bApplyEffectToPlayer{false};
	
	UFUNCTION(BlueprintCallable)
	bool ApplyEffectToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InGameplayEffectSpecHandle);

	void RemoveEffectFromTarget(AActor* TargetActor);

	void RemoveEveryEffect();
	
	UFUNCTION(BlueprintCallable)
	virtual bool OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	virtual bool OnEndOverlap(AActor* TargetActor);
};
