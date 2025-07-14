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
		if (TaggedInputAction.IsValid())
		{
			return TaggedInputAction.InputAction;
		}
	}
	return nullptr;
}
