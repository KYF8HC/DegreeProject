#include "Data/DP_LevelUpInfo.h"

int32 UDP_LevelUpInfo::GetLevelBasedOnExp(int ExperiencePoints) const
{
	int32 Level = 1;

	for (const auto& LevelUpInfo : LevelUpInfoArray)
	{
		if (ExperiencePoints < LevelUpInfo.LevelUpRequirement)
		{
			break;
		}
		Level++;
	}

	return Level;
}

void UDP_LevelUpInfo::PopulateLevelUpInfo()
{
	LevelUpInfoArray.Empty();

	for (int32 i = 0; i < 40; i++)
	{
		FLevelUpInfo LevelUpInfo;
		LevelUpInfo.Level = i + 1;

		int PreviousLevelReq = 0;
		if (i > 0)
			PreviousLevelReq = LevelUpInfoArray[i - 1].LevelUpRequirement;

		LevelUpInfo.LevelUpRequirement = PreviousLevelReq + FMath::RoundToInt(CurveScalar * FMath::Pow(i + 1, CurveExponent) +
			CurveLinearGrowthStabilizer * (i + 1));
		LevelUpInfoArray.Add(LevelUpInfo);
	}
}

#if WITH_EDITOR

void UDP_LevelUpInfo::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	PopulateLevelUpInfo();
}

#endif
