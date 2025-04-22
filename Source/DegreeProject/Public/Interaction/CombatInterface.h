#pragma once

#include "CoreMinimal.h"
#include "Data/DP_CharacterClassInfo.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

UINTERFACE()
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

class DEGREEPROJECT_API ICombatInterface
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintNativeEvent)
	int32 GetCharacterLevel();
	
	virtual FVector GetCombatSocketLocation() = 0;
	virtual void Death() = 0;
	virtual bool IsEnemy() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	ECharacterClass GetCharacterClass();
};
