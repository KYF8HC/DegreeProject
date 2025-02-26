#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "DP_BaseCharacter.generated.h"


class UAttributeSet;
class UAbilitySystemComponent;

UCLASS(Abstract)
class DEGREEPROJECT_API ADP_BaseCharacter : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:

	ADP_BaseCharacter();
	
	//Getters and Setters
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSetRef; }
	virtual int32 GetPlayerLevel() override { return 1; }
protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability System")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponentRef{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Attribute Set")
	TObjectPtr<UAttributeSet> AttributeSetRef{};

};