#include "Core/DP_GameMode.h"
#include "Characters/Enemy/DP_EnemyCharacter.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "Kismet/GameplayStatics.h"
#include "Player/DP_PlayerController.h"

ADP_GameMode::ADP_GameMode()
{
	
}

void ADP_GameMode::OnBegin(bool bFirstTime)
{
	int NumberOfControllers = UGameplayStatics::GetNumPlayerControllers(GetWorld());
	for (int i = 0; i < NumberOfControllers; i++)
	{
		ADP_PlayerController* PlayerController = Cast<ADP_PlayerController>(
			UGameplayStatics::GetPlayerController(GetWorld(), i));
		PlayerController->OnBegin();
	}
	OnBeginDelegate.Broadcast(bFirstTime);

	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &ADP_GameMode::SpawnBotTimerElapsed,
									SpawnTimerInterval, true);
}

void ADP_GameMode::OnBotQueryFinished(UEnvQueryInstanceBlueprintWrapper* QueryInstance,
										   EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("ADP_GameMode::OnBotQueryFinished: QueryStatus is not Success"));
		return;
	}

	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();
	if (Locations.Num() <= 0)
	{
		return;
	}

	AActor* NewEnemy = GetWorld()->SpawnActor<AActor>(EnemyClass, Locations[0], FRotator::ZeroRotator);
	if (!NewEnemy)
	{
		UE_LOG(LogTemp, Error, TEXT("ADP_GameMode::OnBotQueryFinished: NewEnemy is nullptr"));
	}
}

void ADP_GameMode::SpawnBotTimerElapsed()
{
	UEnvQueryInstanceBlueprintWrapper* QueryInstance
		= UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this,
										EEnvQueryRunMode::RandomBest5Pct, nullptr);

	if (ensureMsgf(QueryInstance, TEXT("ADP_GameMode::SpawnBotTimerElapsed: QueryInstance is nullptr")))
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ADP_GameMode::OnBotQueryFinished);
}

void ADP_GameMode::OnUpdate()
{
	OnUpdateDelegate.Broadcast();
}

void ADP_GameMode::OnEnd()
{
	OnEndDelegate.Broadcast();
}

bool ADP_GameMode::IsDone()
{
	return false;
}
