#include "GUI/WidgetController/DP_OverlayWidgetController.h"

#include "Characters/DP_PlayerCharacter.h"
#include "Data/DP_LevelUpInfo.h"
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
	ADP_PlayerCharacter* PlayerCharacter = CastChecked<ADP_PlayerCharacter>(PlayerCharacterRef);
	PlayerCharacter->OnExperiencePointsChanged.
	                 AddUObject(this, &UDP_OverlayWidgetController::OnExperiencePointsChanged);
	PlayerCharacter->OnLevelChanged.AddUObject(this, &UDP_OverlayWidgetController::OnLevelChanged);


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

void UDP_OverlayWidgetController::InitializeWidgetController()
{
	Super::InitializeWidgetController();
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

void UDP_OverlayWidgetController::OnExperiencePointsChanged(const int32 NewExperiencePoints) const
{
	const ADP_PlayerCharacter* PlayerCharacter = CastChecked<ADP_PlayerCharacter>(PlayerCharacterRef);
	const UDP_LevelUpInfo* LevelUpInfo = PlayerCharacter->LevelUpInfo;

	const int32 Level = LevelUpInfo->GetLevelBasedOnExp(NewExperiencePoints);
	const int32 MaxLevel = LevelUpInfo->LevelUpInfoArray.Num();

	if (Level == 1)
	{
		const int32 LevelUpRequirement = LevelUpInfo->LevelUpInfoArray[Level - 1].LevelUpRequirement;
		const int32 XPForThisLevel = NewExperiencePoints;

		const float Percentage = static_cast<float>(XPForThisLevel) / static_cast<float>(LevelUpRequirement);
		OnExperiencePercentageChange.Broadcast(Percentage);
	}

	if (Level <= MaxLevel && Level > 0)
	{
		const int32 LevelUpRequirement = LevelUpInfo->LevelUpInfoArray[Level - 1].LevelUpRequirement;
		const int32 PreviousLevelUpRequirement = Level > 1
			                                         ? LevelUpInfo->LevelUpInfoArray[Level - 2].LevelUpRequirement
			                                         : 0;

		const int32 DeltaLevelRequirement = LevelUpRequirement - PreviousLevelUpRequirement;
		const int32 XPForThisLevel = NewExperiencePoints - PreviousLevelUpRequirement;

		const float Percentage = static_cast<float>(XPForThisLevel) / static_cast<float>(DeltaLevelRequirement);

		OnExperiencePercentageChange.Broadcast(Percentage);
	}
}

void UDP_OverlayWidgetController::OnLevelChanged(const int32 NewLevel)
{
}
