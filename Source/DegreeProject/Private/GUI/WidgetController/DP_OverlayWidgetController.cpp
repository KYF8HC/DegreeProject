#include "GUI/WidgetController/DP_OverlayWidgetController.h"
#include "GameplayAbilities/DP_AttributeSet.h"

void UDP_OverlayWidgetController::BroadcastInitialValues()
{
	UDP_AttributeSet* AttributeSet = CastChecked<UDP_AttributeSet>(AttributeSetRef);
	OnHealthChange.Broadcast(AttributeSet->GetHealth());
	OnMaxHealthChange.Broadcast(AttributeSet->GetMaxHealth());
	OnAbilityResourceChange.Broadcast(AttributeSet->GetAbilityResource());
	OnMaxAbilityResourceChange.Broadcast(AttributeSet->GetMaxAbilityResource());
}

void UDP_OverlayWidgetController::BindCallbacksToDependencies()
{
	UDP_AttributeSet* AttributeSet = CastChecked<UDP_AttributeSet>(AttributeSetRef);

	AbilitySystemComponentRef->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute())
	                         .AddUObject(this, &UDP_OverlayWidgetController::HealthChanged);

	AbilitySystemComponentRef->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxHealthAttribute())
	                         .AddUObject(this, &UDP_OverlayWidgetController::MaxHealthChanged);

	AbilitySystemComponentRef->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetAbilityResourceAttribute())
	                         .AddUObject(this, &UDP_OverlayWidgetController::AbilityResourceChanged);

	AbilitySystemComponentRef->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxAbilityResourceAttribute())
	                         .AddUObject(this, &UDP_OverlayWidgetController::MaxAbilityResourceChanged);
}

void UDP_OverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data)
{
	OnHealthChange.Broadcast(Data.NewValue);
}

void UDP_OverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	OnMaxHealthChange.Broadcast(Data.NewValue);
}

void UDP_OverlayWidgetController::AbilityResourceChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("AbilityResourceChanged: %f"), Data.NewValue);
	OnAbilityResourceChange.Broadcast(Data.NewValue);
}

void UDP_OverlayWidgetController::MaxAbilityResourceChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("MaxAbilityResourceChanged: %f"), Data.NewValue);
	OnMaxAbilityResourceChange.Broadcast(Data.NewValue);
}
