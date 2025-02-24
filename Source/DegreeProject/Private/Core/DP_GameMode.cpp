#include "Core/DP_GameMode.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/PlayerState.h"
#include "GUI/HUD/DP_PlayerHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Player/DP_PlayerController.h"
#include "Player/DP_PlayerState.h"

ADP_GameMode::ADP_GameMode()
{
}

void ADP_GameMode::OnBegin(bool bFirstTime)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		PlayerControllerRef = Cast<ADP_PlayerController>(PlayerController);
		checkf(PlayerControllerRef, TEXT("AGP4_GameMode::SaveReferences: PlayerController is not valid"));
		PlayerControllerRef->SetCanReceiveInput(true);
	}

	if (PlayerControllerRef)
	{
		PlayerHUDRef = Cast<ADP_PlayerHUD>(PlayerControllerRef->GetHUD());
		ADP_PlayerState* PlayerState = Cast<ADP_PlayerState>(PlayerControllerRef->PlayerState);

		checkf(PlayerHUDRef, TEXT("AGP4_GameMode::SaveReferences: HUD is not valid"));
		PlayerHUDRef->InitOverlay(PlayerControllerRef,
		                          PlayerState,
		                          UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(PlayerState),
		                          PlayerState->GetAttributeSet());
		
		OnBeginDelegate.Broadcast(bFirstTime);
	}
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
