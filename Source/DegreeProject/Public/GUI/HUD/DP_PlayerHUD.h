#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DP_PlayerHUD.generated.h"

class UDP_UserWidgetBase;

UCLASS()
class DEGREEPROJECT_API ADP_PlayerHUD : public AHUD
{
	GENERATED_BODY()
public:

	UPROPERTY()
	TObjectPtr<UDP_UserWidgetBase> OverlayWidgetRef{};
protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDP_UserWidgetBase> OverlayWidgetClass{};
};
