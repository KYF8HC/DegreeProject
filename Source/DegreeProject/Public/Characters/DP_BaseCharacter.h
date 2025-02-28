#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Data/DP_CharacterClassInfo.h"
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
	virtual FVector GetCombatSocketLocation() override { return  WeaponSocketComponentRef->GetComponentLocation(); }
	virtual void Death() override;
protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability System")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponentRef{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Attribute Set")
	TObjectPtr<UAttributeSet> AttributeSetRef{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat")
	TObjectPtr<USceneComponent> WeaponSocketComponentRef{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Defaults")
	int32 Level{1};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Defaults")
	ECharacterClass CharacterClass{ECharacterClass::Warrior};
	
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
	//FName WeaponSocketName{TEXT("WeaponSocket")};

	virtual void BeginPlay() override;
};