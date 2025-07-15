#include "Ability/CharacterSprintAbility.h"
#include "Abilities/GameplayAbility.h"
#include "Character/AnimeGirlCharacter.h"
#include "Character/CharacterAttributeSet.h"

UCharacterSprintAbility::UCharacterSprintAbility()
{
	InitStaminaCost = 6.0f;
	OnGoingStaminaCost = 2.0f;
	SpeedUpEffect = nullptr;
	ExhaustionEffect = nullptr;
}

bool UCharacterSprintAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	UCharacterAttributeSet* CharacterAttributeSet = GetAttributeSetOfOwner(ActorInfo);
	if (CharacterAttributeSet)
	{
		return CharacterAttributeSet->GetStamina() >= InitStaminaCost;
	}
	return false;
}

bool UCharacterSprintAbility::CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags)
{
	if (!Super::CommitAbility(Handle, ActorInfo, ActivationInfo, OptionalRelevantTags))
	{
		return false;
	}

	UCharacterAttributeSet* CharacterAttributeSet = GetAttributeSetOfOwner(ActorInfo);
	if (CharacterAttributeSet)
	{
		float OldValue = CharacterAttributeSet->GetStamina();
		float NewValue = OldValue - InitStaminaCost;
		CharacterAttributeSet->SetStamina(NewValue);
	}
	return true;
}

void UCharacterSprintAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		return;
	}

	if (SpeedUpEffect)
	{
		FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(SpeedUpEffect);
		SpeedUpEffectHandle = ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, EffectSpecHandle);
	}

	if (UWorld* World = GetWorld())
	{
		FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &UCharacterSprintAbility::AbilityLoopFunction, Handle, ActorInfo, ActivationInfo);
		World->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, LoopTimerInterval, true);
	}
}

void UCharacterSprintAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

	if (UWorld* World = GetWorld())
	{
		if (TimerHandle.IsValid())
		{
			World->GetTimerManager().ClearTimer(TimerHandle);
		}
	}
	if (SpeedUpEffectHandle.IsValid())
	{
		BP_RemoveGameplayEffectFromOwnerWithHandle(SpeedUpEffectHandle);
	}

	if (ExhaustionEffect)
	{
		FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(ExhaustionEffect);
		SpeedUpEffectHandle = ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, EffectSpecHandle);
	}
}

UCharacterAttributeSet* UCharacterSprintAbility::GetAttributeSetOfOwner(const FGameplayAbilityActorInfo* ActorInfo) const
{
	const AActor* Actor = ActorInfo->AvatarActor.Get();
	if (const AAnimeGirlCharacter* Character = CastChecked<AAnimeGirlCharacter>(Actor, ECastCheckedType::NullAllowed))
	{
		if (const UAbilitySystemComponent* ACS = Character->GetAbilitySystemComponent())
		{
			const UAttributeSet* AttributeSet = ACS->GetAttributeSet(UCharacterAttributeSet::StaticClass());
			const UCharacterAttributeSet* CharacterAttributeSet = Cast<UCharacterAttributeSet>(AttributeSet);
			return (UCharacterAttributeSet *)CharacterAttributeSet;
		}
	}
	return nullptr;
}

void UCharacterSprintAbility::AbilityLoopFunction(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	UCharacterAttributeSet* CharacterAttributeSet = GetAttributeSetOfOwner(ActorInfo);
	if (CharacterAttributeSet)
	{
		float OldValue = CharacterAttributeSet->GetStamina();
		float NewValue = OldValue - OnGoingStaminaCost;
		if (NewValue >= 0)
		{
			CharacterAttributeSet->SetStamina(NewValue);
		}
		else
		{
			CancelAbility(Handle, ActorInfo, ActivationInfo, false);
		}
	}
}
