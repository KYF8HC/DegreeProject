#pragma once

#include "CoreMinimal.h"
#include "Characters/DP_BaseCharacter.h"
#include "Data/DP_CharacterClassInfo.h"
#include "DP_EnemyCharacter.generated.h"

enum class ECharacterClass : uint8;
class UWidgetComponent;
class UDP_AIMoveEvent;
class UDP_AIBaseEvent;
class IDP_Event;
class UDP_EventHandler;

UCLASS()
class DEGREEPROJECT_API ADP_EnemyCharacter : public ADP_BaseCharacter
{
	GENERATED_BODY()

public:
	ADP_EnemyCharacter();
	void StartDefaultEvent();

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Events")
	TObjectPtr<UDP_EventHandler> EnemyEventHandlerRef{};

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Events")
	TArray<FVector> PatrolPath{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Events")
	TSubclassOf<UDP_AIBaseEvent> DefaultEventClass{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Defaults")
	int32 Level{1};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Defaults")
	ECharacterClass CharacterClass{ECharacterClass::Warrior};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBarWidgetComponent{};
	
	UPROPERTY(BlueprintReadOnly, Category="AI", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UDP_AIMoveEvent> MoveEventRef{};
	
	UFUNCTION()
	void OnBegin(bool bFirstTime);
	
	virtual void BeginPlay() override;
};
