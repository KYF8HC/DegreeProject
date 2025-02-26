#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "DP_AssetManager.generated.h"


UCLASS()
class DEGREEPROJECT_API UDP_AssetManager : public UAssetManager
{
	GENERATED_BODY()

public:

	static UDP_AssetManager& Get();

protected:

	virtual void StartInitialLoading() override;
};
