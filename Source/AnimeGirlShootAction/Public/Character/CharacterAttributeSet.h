#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h" // For MACRO
#include "CharacterAttributeSet.generated.h"

// struct getter, value getter, value setter, value init
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(
	FAttributeChangedEvent,
	UAttributeSet*, AttributeSet,
	float, OldValue,
	float, NewValue);

UCLASS()
class ANIMEGIRLSHOOTACTION_API UCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UCharacterAttributeSet();
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayAttributeData MaxStamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Stamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayAttributeData MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayAttributeData MovementSpeed;

	UPROPERTY(BlueprintAssignable)
	FAttributeChangedEvent OnStaminaChanged;

	UPROPERTY(BlueprintAssignable)
	FAttributeChangedEvent OnMovementSpeedChanged;

	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, MaxStamina)
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Stamina)
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, MaxHealth)
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Health)
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, MovementSpeed)
};
