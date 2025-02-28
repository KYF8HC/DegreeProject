#include "Characters/Enemy/DP_EnemyCharacter.h"
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
	UE_LOG(LogTemp, Log, TEXT("ADP_EnemyCharacter::BeginPlay"));
	AbilitySystemComponentRef->InitAbilityActorInfo(this, this);
	UDP_AbilitySystemLibrary::GiveStartupAbilities(this, CharacterClass, AbilitySystemComponentRef);

	StartDefaultEvent();
}
