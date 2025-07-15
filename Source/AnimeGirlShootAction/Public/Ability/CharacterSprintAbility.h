#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ActiveGameplayEffectHandle.h"
#include "CharacterSprintAbility.generated.h"

class UCharacterAttributeSet;
class UGameplayEffect;

UCLASS()
class ANIMEGIRLSHOOTACTION_API UCharacterSprintAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UCharacterSprintAbility();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sprint|Effect")
	TSubclassOf<UGameplayEffect> SpeedUpEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sprint|Effect")
	TSubclassOf<UGameplayEffect> ExhaustionEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sprint|Attributes")
	float InitStaminaCost;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sprint|Attributes")
	float OnGoingStaminaCost;

	virtual bool CanActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayTagContainer* SourceTags = nullptr,
		const FGameplayTagContainer* TargetTags = nullptr,
		FGameplayTagContainer* OptionalRelevantTags = nullptr
	) const override;

	virtual bool CommitAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		OUT FGameplayTagContainer* OptionalRelevantTags = nullptr
	) override;

	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData
	) override;

	virtual void CancelAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		bool bReplicateCancelAbility
	) override;

private:

	FActiveGameplayEffectHandle SpeedUpEffectHandle;
	FTimerHandle TimerHandle;
	float LoopTimerInterval = 0.1f;

	UCharacterAttributeSet* GetAttributeSetOfOwner(const FGameplayAbilityActorInfo* ActorInfo) const;

	void AbilityLoopFunction(
		const FGameplayAbilitySpecHandle Handle, 
		const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo);
};
