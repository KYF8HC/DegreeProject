#include "GUI/WidgetController/DP_OverlayWidgetController.h"
#include "GameplayAbilities/DP_AttributeSet.h"

void UDP_OverlayWidgetController::BroadcastInitialValues()
{
	UDP_AttributeSet* AttributeSet = CastChecked<UDP_AttributeSet>(AttributeSetRef);
	AttributeSet->GetHealthAttribute();
	OnHealthChange.Broadcast(AttributeSet->GetHealth());
	OnMaxHealthChange.Broadcast(AttributeSet->GetMaxHealth());
}

void UDP_OverlayWidgetController::BindCallbacksToDependencies()
{
	UDP_AttributeSet* AttributeSet = CastChecked<UDP_AttributeSet>(AttributeSetRef);

	if (AttributeSet->GetHealthAttribute() == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UDP_OverlayWidgetController::BindCallbacksToDependencies: Health attribute is null!"));
		
		//AbilitySystemComponentRef->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute())
		//                         .AddUObject(this, &UDP_OverlayWidgetController::HealthChanged);

		//AbilitySystemComponentRef->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxHealthAttribute())
		//                         .AddUObject(this, &UDP_OverlayWidgetController::MaxHealthChanged);
	}
}

void UDP_OverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data)
{
	OnHealthChange.Broadcast(Data.NewValue);
}

void UDP_OverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	OnMaxHealthChange.Broadcast(Data.NewValue);
}
