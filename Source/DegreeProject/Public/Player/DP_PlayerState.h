
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "DP_PlayerState.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

UCLASS(Abstract)
class DEGREEPROJECT_API ADP_PlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	ADP_PlayerState();

	//Getters and Setters
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSetRef; }
	
protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponentRef{};

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAttributeSet> AttributeSetRef{};
};
