#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DP_PlayerInterface.generated.h"

struct FGameplayTagContainer;
struct FGameplayTag;

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
	FGameplayTagContainer GetOwnedWeapons() const;
	
	UFUNCTION(BlueprintNativeEvent)
	void GrantWeaponTag(FGameplayTag WeaponTag);
	
	UFUNCTION(BlueprintNativeEvent)
	int32 GetLevelBasedOnExp(int32 InExperiencePoints);
	
	UFUNCTION(BlueprintNativeEvent)
	void AddToPlayerExperience(int32 ExperienceAmount);

	UFUNCTION(BlueprintNativeEvent)
	int32 GetPlayerExperience() const;
	
	UFUNCTION(BlueprintNativeEvent)
	void LevelUp();
};
