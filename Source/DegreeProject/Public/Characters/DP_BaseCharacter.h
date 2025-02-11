#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "DP_BaseCharacter.generated.h"


class UAttributeSet;
class UAbilitySystemComponent;

UCLASS(Abstract)
class DEGREEPROJECT_API ADP_BaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	ADP_BaseCharacter();
	
	//Getters and Setters
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSetRef; }

protected:

	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponentRef{};

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSetRef{};

};