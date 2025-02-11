#include "GUI/HUD/DP_PlayerHUD.h"
#include "GUI/Widgets/DP_UserWidgetBase.h"

void ADP_PlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}
