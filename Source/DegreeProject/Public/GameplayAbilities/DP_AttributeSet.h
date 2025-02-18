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



UCLASS()
class DEGREEPROJECT_API UDP_AttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UDP_AttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UDP_AttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UDP_AttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes", ReplicatedUsing = OnRep_AbilityResource)
	FGameplayAttributeData AbilityResource;
	ATTRIBUTE_ACCESSORS(UDP_AttributeSet, AbilityResource)

	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes", ReplicatedUsing = OnRep_MaxAbilityResource)
	FGameplayAttributeData MaxAbilityResource;
	ATTRIBUTE_ACCESSORS(UDP_AttributeSet, MaxAbilityResource)
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	
	UFUNCTION()
	void OnRep_AbilityResource(const FGameplayAttributeData& OldAbilityResource);
	
	UFUNCTION()
	void OnRep_MaxAbilityResource(const FGameplayAttributeData& OldMaxAbilityResource);
};


