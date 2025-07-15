#include "Character/CharacterAttributeSet.h"

UCharacterAttributeSet::UCharacterAttributeSet()
{
	// TODO: ���� �ϵ��ڵ��� ���� ���� ��� �� �� ������...?
	InitMaxStamina(100.0f);
	InitStamina(100.0f);
	InitMovementSpeed(400.0f);
}

void UCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	// TODO: Current ���� Max ���� �����ϴ� �ȶ��� ����� �ʿ���
	// TODO: �ٵ� �׷� ����� ������?
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
