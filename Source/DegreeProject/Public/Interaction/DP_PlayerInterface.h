#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DP_PlayerInterface.generated.h"

UINTERFACE()
class UDP_PlayerInterface : public UInterface
{
	GENERATED_BODY()
};

class DEGREEPROJECT_API IDP_PlayerInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
	void AddToPlayerExperience(int32 ExperienceAmount);
};
