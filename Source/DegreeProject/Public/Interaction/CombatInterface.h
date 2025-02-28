#pragma once

#include "CoreMinimal.h"
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
	virtual int32 GetPlayerLevel() = 0;
	virtual FVector GetCombatSocketLocation() = 0;
	virtual void Death() = 0;
};
