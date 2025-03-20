#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "DP_AttributeSet.generated.h"

/**
 * Creates Accessors for a given attribute. More information can be found in AttributeSet.h!
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties() {}

	FGameplayEffectContextHandle EffectContextHandle{};

	UPROPERTY()
	UAbilitySystemComponent* SourceASC{};

	UPROPERTY()
	AActor* SourceAvatarActor{};

	UPROPERTY()
	AController* SourceController{};

	UPROPERTY()
	ACharacter* SourceCharacter{};

	UPROPERTY()
	UAbilitySystemComponent* TargetASC{};

	UPROPERTY()
	AActor* TargetAvatarActor{};

	UPROPERTY()
	AController* TargetController{};

	UPROPERTY()
	ACharacter* TargetCharacter{};
};

UCLASS()
class DEGREEPROJECT_API UDP_AttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UDP_AttributeSet();

#pragma region Vital Attributes

	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UDP_AttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes", ReplicatedUsing = OnRep_AbilityResource)
	FGameplayAttributeData AbilityResource;
	ATTRIBUTE_ACCESSORS(UDP_AttributeSet, AbilityResource)

#pragma endregion 

#pragma region Primary Attributes
	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UDP_AttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes", ReplicatedUsing = OnRep_MaxAbilityResource)
	FGameplayAttributeData MaxAbilityResource;
	ATTRIBUTE_ACCESSORS(UDP_AttributeSet, MaxAbilityResource)
	
	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes", ReplicatedUsing = OnRep_Stamina)
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UDP_AttributeSet, Stamina)

	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes", ReplicatedUsing = OnRep_Armor)
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UDP_AttributeSet, Armor)

	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes", ReplicatedUsing = OnRep_MagicResist)
	FGameplayAttributeData MagicResist;
	ATTRIBUTE_ACCESSORS(UDP_AttributeSet, MagicResist)

#pragma endregion
	
#pragma region Special Attributes
	UPROPERTY(BlueprintReadOnly, Category = "Special Attributes", ReplicatedUsing = OnRep_Strength)
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UDP_AttributeSet, Strength)

	UPROPERTY(BlueprintReadOnly, Category = "Special Attributes", ReplicatedUsing = OnRep_Agility)
	FGameplayAttributeData Agility;
	ATTRIBUTE_ACCESSORS(UDP_AttributeSet, Agility)

	UPROPERTY(BlueprintReadOnly, Category = "Special Attributes", ReplicatedUsing = OnRep_Intellect)
	FGameplayAttributeData Intellect;
	ATTRIBUTE_ACCESSORS(UDP_AttributeSet, Intellect)
#pragma endregion

#pragma region Secondary Attributes
	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes", ReplicatedUsing = OnRep_AbilityHaste)
	FGameplayAttributeData AbilityHaste;
	ATTRIBUTE_ACCESSORS(UDP_AttributeSet, AbilityHaste)

	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes", ReplicatedUsing = OnRep_Mastery)
	FGameplayAttributeData Mastery;
	ATTRIBUTE_ACCESSORS(UDP_AttributeSet, Mastery)

	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes", ReplicatedUsing = OnRep_CriticalStrikeChance)
	FGameplayAttributeData CriticalStrikeChance;
	ATTRIBUTE_ACCESSORS(UDP_AttributeSet, CriticalStrikeChance)

	UPROPERTY(BlueprintReadOnly, Category= "Secondary Attributes", ReplicatedUsing = OnRep_CriticalStrikeDamage)
	FGameplayAttributeData CriticalStrikeDamage;
	ATTRIBUTE_ACCESSORS(UDP_AttributeSet, CriticalStrikeDamage)

	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes", ReplicatedUsing = OnRep_DodgeChance)
	FGameplayAttributeData DodgeChance;
	ATTRIBUTE_ACCESSORS(UDP_AttributeSet, DodgeChance)

	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes", ReplicatedUsing = OnRep_ArmorPenetration)
	FGameplayAttributeData ArmorPenetration;
#pragma endregion

	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UDP_AttributeSet, IncomingDamage)

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

#pragma region OnRep Functions
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

	UFUNCTION()
	void OnRep_AbilityResource(const FGameplayAttributeData& OldAbilityResource);

	UFUNCTION()
	void OnRep_MaxAbilityResource(const FGameplayAttributeData& OldMaxAbilityResource);

	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldStamina);
	
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor);
	
	UFUNCTION()
	void OnRep_MagicResist(const FGameplayAttributeData& OldMagicResist);
	
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength);
	
	UFUNCTION()
	void OnRep_Agility(const FGameplayAttributeData& OldAgility);
	
	UFUNCTION()
	void OnRep_Intellect(const FGameplayAttributeData& OldIntellect);
	
	UFUNCTION()
	void OnRep_AbilityHaste(const FGameplayAttributeData& OldAbilityHaste);
	
	UFUNCTION()
	void OnRep_Mastery(const FGameplayAttributeData& OldMastery);
	
	UFUNCTION()
	void OnRep_CriticalStrikeChance(const FGameplayAttributeData& OldCriticalStrikeChance);

	UFUNCTION()
	void OnRep_CriticalStrikeDamage(const FGameplayAttributeData& OldCriticalStrikeDamage);
	
	UFUNCTION()
	void OnRep_DodgeChance(const FGameplayAttributeData& OldDodgeChance);

	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration);
#pragma endregion

private:
	
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;

};
