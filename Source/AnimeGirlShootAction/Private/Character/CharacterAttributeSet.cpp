#include "Character/CharacterAttributeSet.h"

UCharacterAttributeSet::UCharacterAttributeSet()
{
	// TODO: 여기 하드코딩한 값을 어디로 어떻게 뺄 수 있을까...?
	InitMaxStamina(100.0f);
	InitStamina(100.0f);
	InitMovementSpeed(400.0f);
}

void UCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	// TODO: Current 값과 Max 값을 관리하는 똑똑한 방법이 필요해
	// TODO: 근데 그런 방법이 있을까?
	if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxStamina());
	}
	Super::PreAttributeChange(Attribute, NewValue);
}

void UCharacterAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	if (Attribute == GetStaminaAttribute())
	{
		;
	}
	if (Attribute == GetMovementSpeedAttribute())
	{
		OnMovementSpeedChanged.Broadcast(this, OldValue, NewValue);
	}
}
