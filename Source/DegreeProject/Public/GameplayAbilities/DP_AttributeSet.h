#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "DP_AttributeSet.generated.h"

#pragma region FGameplayAttributeData boilerplate code

/**
 * Creates Accessors for a given attribute. More information can be found in AttributeSet.h!
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * Defines the declaration of a new attribute
 * @param ClassName the name of the class that will contain the attribute
 * @param PropertyName the name of the UPROPERTY
 * @param PropertyType the category of the UPROPERTY
 *
 * Usage:
 * DECLARE_GAS_ATTRIBUTE(UMyAttributeSet, MyHealth, "MyCategory")
 * 
 * Example:
 * 
 * UPROPERTY(BlueprintReadOnly, Category = "MyCategory", ReplicatedUsing = OnRep_MyHealth)
 * 
 * FGameplayAttributeData MyHealth;
 * 
 * ATTRIBUTE_ACCESSORS(UMyAttributeSet, MyHealth)
 * 
 * UFUNCTION()
 * void OnRep_MyHealth(const FGameplayAttributeData& OldMyHealth);
 */
#define DECLARE_GAS_ATTRIBUTE(ClassName, PropertyName, PropertyType) \
UPROPERTY(BlueprintReadOnly, Category = PropertyType, ReplicatedUsing = OnRep_##PropertyName) FGameplayAttributeData PropertyName; \
ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
UFUNCTION() \
void OnRep_##PropertyName(const FGameplayAttributeData& Old##PropertyName);


/**
 * Defines the implementation of an attribute's OnRep_MyAttribute function
 * Example:
 * void UMyAttributeSet::OnRep_MyHealth(const FGameplayAttributeData& OldMyHealth)
 * {
 * GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, MyHealth, OldMyHealth);
 * }
 * 
 * Usage:
 * IMPLEMENT_GAS_ATTRIBUTE(UMyAttributeSet, MyHealth)
 */
#define IMPLEMENT_GAS_ATTRIBUTE(ClassName, PropertyName) \
void ClassName::OnRep_##PropertyName(const FGameplayAttributeData& Old##PropertyName) \
{ \
	GAMEPLAYATTRIBUTE_REPNOTIFY(ClassName, PropertyName, Old##PropertyName); \
}

#pragma endregion

UCLASS()
class DEGREEPROJECT_API UDP_AttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	UDP_AttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UDP_AttributeSet, Health)
//
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth);

	//DECLARE_GAS_ATTRIBUTE(UPROPERTY, UDP_AttributeSet, Health, "Vital Attributes")
	DECLARE_GAS_ATTRIBUTE(UDP_AttributeSet, MaxHealth, "Vital Attributes")
	DECLARE_GAS_ATTRIBUTE(UDP_AttributeSet, AbilityResource, "Vital Attributes")
	DECLARE_GAS_ATTRIBUTE(UDP_AttributeSet, MaxAbilityResource, "Vital Attributes")

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetHealthBP() const { return Health.GetCurrentValue(); }
	
};


