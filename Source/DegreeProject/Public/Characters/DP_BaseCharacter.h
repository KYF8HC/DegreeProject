#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Data/DP_CharacterClassInfo.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "DP_BaseCharacter.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnCharacterStatChanged, int32 /* Stat value*/);

UCLASS(Abstract)
class DEGREEPROJECT_API ADP_BaseCharacter : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:

	ADP_BaseCharacter();

	FOnCharacterStatChanged OnExperiencePointsChanged;
	FOnCharacterStatChanged OnLevelChanged;
	
	//Getters and Setters
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSetRef; }
	virtual int32 GetCharacterLevel() override { return Level; }
	virtual FVector GetCombatSocketLocation() override { return  WeaponSocketComponentRef->GetComponentLocation(); }
	virtual void Death() override;
	virtual bool IsEnemy() override { return true; }

	FORCEINLINE int32 GetCharacterLevel() const { return Level; }
	FORCEINLINE int32 GetExperiencePoints() const { return ExperiencePoints; }

	void SetCharacterLevel(const int32 NewLevel);
	void AddToLevel(const int32 Amount);
	
	void SetExperiencePoints(const int32 NewExperiencePoints);
	void AddToExperiencePoints(const int32 Amount);
	
	virtual ECharacterClass GetCharacterClass_Implementation() override;
protected:

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability System")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponentRef{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Attribute Set")
	TObjectPtr<UAttributeSet> AttributeSetRef{};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat")
	TObjectPtr<USceneComponent> WeaponSocketComponentRef{};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Character Defaults")
	int32 Level{1};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Character Defaults")
	int32 ExperiencePoints{0};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Defaults")
	ECharacterClass CharacterClass{ECharacterClass::Warrior};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Visual Efefcts")
	TObjectPtr<UMaterialInstance> DissolveMaterialInstanceRef{};
	
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
	//FName WeaponSocketName{TEXT("WeaponSocket")};

	virtual void BeginPlay() override;

};