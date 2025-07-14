#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Input/InputConfig.h"
#include "AnimeGirlEnhancedInputComponent.generated.h"

UCLASS()
class ANIMEGIRLSHOOTACTION_API UAnimeGirlEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
	void BindTaggedActions(
		const UInputConfig* InputConfig,
		UserClass* Object,
		PressedFuncType PressedFunc,
		ReleasedFuncType ReleasedFunc);
};

template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
void UAnimeGirlEnhancedInputComponent::BindTaggedActions(const UInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc)
{
	check(InputConfig);

	for (auto& TaggedAction : InputConfig->TaggedInputActions)
	{
		if (TaggedAction.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(TaggedAction.InputAction, ETriggerEvent::Triggered, Object, PressedFunc, TaggedAction.InputTag);
			}
			if (ReleasedFunc)
			{
				BindAction(TaggedAction.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, TaggedAction.InputTag);
			}
		}
	}
}
