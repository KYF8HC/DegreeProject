#pragma once

#include "CoreMinimal.h"
#include "Data/DP_CharacterClassInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DP_AbilitySystemLibrary.generated.h"


struct FGameplayEffectContextHandle;
class UAbilitySystemComponent;

UCLASS()
class DEGREEPROJECT_API UDP_AbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="DPAblitySystemLibrary | Character Class Defautls")
	static void InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable, Category="DPAblitySystemLibrary | Character Class Defautls")
	static void GiveStartupAbilities(const UObject* WorldContextObject, ECharacterClass CharacterClass, UAbilitySystemComponent* AbilitySystemComponent);

	UFUNCTION(BlueprintCallable, Category="DPAbilitySystemLibrary | Character Class Defaults")
	static UDP_CharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category="DPAbilitySystemLibrary | Gameplay Effects")
	static bool IsDodgedHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="DPAbilitySystemLibrary | Gameplay Effects")
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintCallable, Category="DPAbilitySystemLibrary | Gameplay Effects")
	static void SetIsDodgedHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsDodgedHit);

	UFUNCTION(BlueprintCallable, Category="DPAbilitySystemLibrary | Gameplay Effects")
	static void SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit);
};
