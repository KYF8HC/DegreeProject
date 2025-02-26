#include "Characters/Enemy/DP_EnemyCharacter.h"

#include "AIController.h"
#include "Core/DP_GameMode.h"
#include "Core/Events/AI/DP_AIMoveEvent.h"
#include "Core/Events/DP_EventHandler.h"
#include "GameplayAbilities/DP_AbilitySystemComponent.h"
#include "GameplayAbilities/DP_AbilitySystemLibrary.h"
#include "GameplayAbilities/DP_AttributeSet.h"


ADP_EnemyCharacter::ADP_EnemyCharacter()
{
	AbilitySystemComponentRef = CreateDefaultSubobject<UDP_AbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponentRef->SetIsReplicated(true);
	AbilitySystemComponentRef->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSetRef = CreateDefaultSubobject<UDP_AttributeSet>(TEXT("AttributeSet"));

	EnemyEventHandlerRef = CreateDefaultSubobject<UDP_EventHandler>(TEXT("EnemyEventHandler"));
	EnemyEventHandlerRef->SetIsReplicated(true);
}

void ADP_EnemyCharacter::StartDefaultEvent()
{
	MoveEventRef = NewObject<UDP_AIMoveEvent>(this, DefaultEventClass);
	MoveEventRef->SetController(Cast<AAIController>(GetController()));
	MoveEventRef->SetDependencies(PatrolPath);
	EnemyEventHandlerRef->PushEvent(MoveEventRef);
}

void ADP_EnemyCharacter::OnBegin(bool bFirstTime)
{
	StartDefaultEvent();
}

void ADP_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponentRef->InitAbilityActorInfo(this, this);

	ADP_GameMode* GameMode = Cast<ADP_GameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
		GameMode->OnBeginDelegate.AddDynamic(this, &ADP_EnemyCharacter::OnBegin);

	if (HasAuthority())
	{
		UDP_AbilitySystemLibrary::GiveStartupAbilities(this, CharacterClass, AbilitySystemComponentRef);
	}
	//StartDefaultEvent();
}
