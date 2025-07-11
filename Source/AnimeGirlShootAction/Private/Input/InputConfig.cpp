#include "Input/InputConfig.h"
#include "GameplayTagContainer.h"
#include "EnhancedInput/Public/InputAction.h"

FTaggedInputAction::FTaggedInputAction() : InputAction(nullptr), InputTag()
{
}

const UInputAction* UInputConfig::FindInputActionByTag(const FGameplayTag& InputTag) const
{
	for (auto& TaggedInputAction : TaggedInputActions)
	{
		if (TaggedInputAction.InputAction && TaggedInputAction.InputTag == InputTag)
		{
			return TaggedInputAction.InputAction;
		}
	}
	return nullptr;
}
