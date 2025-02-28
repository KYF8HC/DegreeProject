#include "Characters/Enemy/DP_EnemyCharacter.h"
#include "Components/WidgetComponent.h"
#include "Core/Events/DP_EventHandler.h"
#include "GameplayAbilities/DP_AbilitySystemComponent.h"
#include "GameplayAbilities/DP_AbilitySystemLibrary.h"
#include "GameplayAbilities/DP_AttributeSet.h"
#include "GUI/Widgets/DP_UserWidgetBase.h"


ADP_EnemyCharacter::ADP_EnemyCharacter()
{
	AbilitySystemComponentRef = CreateDefaultSubobject<UDP_AbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponentRef->SetIsReplicated(true);
	AbilitySystemComponentRef->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSetRef = CreateDefaultSubobject<UDP_AttributeSet>(TEXT("AttributeSet"));

	EnemyEventHandlerRef = CreateDefaultSubobject<UDP_EventHandler>(TEXT("EnemyEventHandler"));
	EnemyEventHandlerRef->SetIsReplicated(true);

	HealthBarWidgetComponentRef = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HealthBarWidgetComponentRef->SetupAttachment(GetRootComponent());
}

//void ADP_EnemyCharacter::StartDefaultEvent()
//{
//	MoveEventRef = NewObject<UDP_AIMoveEvent>(this, DefaultEventClass);
//	MoveEventRef->SetController(Cast<AAIController>(GetController()));
//	MoveEventRef->SetDependencies(PatrolPath);
//	EnemyEventHandlerRef->PushEvent(MoveEventRef);
//}

void ADP_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponentRef->InitAbilityActorInfo(this, this);
	UDP_AbilitySystemLibrary::GiveStartupAbilities(this, CharacterClass, AbilitySystemComponentRef);

	StartDefaultEvent();

	if (UDP_UserWidgetBase* Widget = Cast<UDP_UserWidgetBase>(HealthBarWidgetComponentRef->GetUserWidgetObject()))
	{
		Widget->SetWidgetController(this);
	}

	UDP_AttributeSet* AttributeSet = Cast<UDP_AttributeSet>(AttributeSetRef);
	if (AttributeSet)
	{
		AbilitySystemComponentRef->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).
		                           AddLambda(
			                           [this](const FOnAttributeChangeData& Data)
			                           {
				                           OnHealthChangeDelegate.Broadcast(Data.NewValue);
			                           });

		AbilitySystemComponentRef->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxHealthAttribute()).
		                           AddLambda(
			                           [this](const FOnAttributeChangeData& Data)
			                           {
				                           OnMaxHealthChangeDelegate.Broadcast(Data.NewValue);
			                           });

		OnHealthChangeDelegate.Broadcast(AttributeSet->GetHealth());
		OnMaxHealthChangeDelegate.Broadcast(AttributeSet->GetMaxHealth());
	}
}
