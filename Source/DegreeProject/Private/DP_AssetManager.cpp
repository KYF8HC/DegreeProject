#include "DP_AssetManager.h"
#include "FDP_GameplayTags.h"

UDP_AssetManager& UDP_AssetManager::Get()
{
	check(GEngine);

	UDP_AssetManager* AssetManager = Cast<UDP_AssetManager>(GEngine->AssetManager);
	return *AssetManager;
}

void UDP_AssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FDP_GameplayTags::InitializeNativeGameplayTags();
}
