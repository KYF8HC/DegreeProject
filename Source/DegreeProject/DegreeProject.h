#pragma once

#include "CoreMinimal.h"

#define ECC_Projectile ECollisionChannel::ECC_GameTraceChannel1

static void LogOnScreen(const UObject* WorldContext, FString Msg, const FColor Color = FColor::White,
                        const float Time = 5.0f)
{
	if (!ensure(WorldContext))
	{
		return;
	}

	UWorld* World = WorldContext->GetWorld();
	if (!ensure(World))
	{
		return;
	}

	FString NetPrefix = World->IsNetMode(NM_Client) ? "[CLIENT]: " : "[SERVER]: ";
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Time, Color, NetPrefix + Msg);
	}
}
