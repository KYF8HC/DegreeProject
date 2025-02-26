#pragma once

#include "CoreMinimal.h"
#include "Data/DP_CharacterClassInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DP_AbilitySystemLibrary.generated.h"


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
	
};
