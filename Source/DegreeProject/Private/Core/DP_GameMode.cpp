#include "Core/DP_GameMode.h"
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
