#include "Ability/AbilitySet.h"
#include "Abilities/GameplayAbility.h"

FTaggedAbility::FTaggedAbility() : Ability(nullptr), AbilityLevel(1), InputTag()
{
}

TSubclassOf<UGameplayAbility> UAbilitySet::FindAbilityClassByTag(const FGameplayTag& InputTag) const
{
	for (auto& TaggedAbility : TaggedAbilities)
	{
		if (TaggedAbility.Ability && TaggedAbility.InputTag == InputTag)
		{
			return TaggedAbility.Ability;
		}
	}
	return nullptr;
}

