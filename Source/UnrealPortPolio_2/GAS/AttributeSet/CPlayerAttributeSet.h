#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CPlayerAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class UNREALPORTPOLIO_2_API UCPlayerAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

public:
	UPROPERTY(EditDefaultsOnly, Category = "GAS Attribute", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData BaseHealth;
	ATTRIBUTE_ACCESSORS(UCPlayerAttributeSet, BaseHealth);

	UPROPERTY(EditDefaultsOnly, Category = "GAS Attribute", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UCPlayerAttributeSet, CurrentHealth);

	UPROPERTY(EditDefaultsOnly, Category = "GAS Attribute", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData BaseDamage;
	ATTRIBUTE_ACCESSORS(UCPlayerAttributeSet, BaseDamage);

	UPROPERTY(EditDefaultsOnly, Category = "GAS Attribute", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CurrentDamage;
	ATTRIBUTE_ACCESSORS(UCPlayerAttributeSet, CurrentDamage);

	UPROPERTY(EditDefaultsOnly, Category = "GAS Attribute", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData BaseDefense;
	ATTRIBUTE_ACCESSORS(UCPlayerAttributeSet, BaseDefense);

	UPROPERTY(EditDefaultsOnly, Category = "GAS Attribute", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CurrentDefense;
	ATTRIBUTE_ACCESSORS(UCPlayerAttributeSet, CurrentDefense);
};
