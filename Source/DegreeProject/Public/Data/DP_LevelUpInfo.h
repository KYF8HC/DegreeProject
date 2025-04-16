#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DP_LevelUpInfo.generated.h"

USTRUCT(BlueprintType)
struct FLevelUpInfo
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Level{0};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 LevelUpRequirement{0};
};

UCLASS()
class DEGREEPROJECT_API UDP_LevelUpInfo : public UDataAsset
{
	GENERATED_BODY()


public:

	UFUNCTION()
	int32 GetLevelBasedOnExp(int ExperiencePoints) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level Up Info")
	TArray<FLevelUpInfo> LevelUpInfoArray{};
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level Up Info")
	float CurveScalar{0.0f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level Up Info")
	float CurveExponent{0.0f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level Up Info")
	float CurveLinearGrowthStabilizer{0.0f};

	void PopulateLevelUpInfo();
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
};
