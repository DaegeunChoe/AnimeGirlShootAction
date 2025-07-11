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

	for (auto& Action : InputConfig->TaggedInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Action->InputAction, ETriggerEvent::Triggered, Object, PressedFunc, Action->InputTag);
			}
			if (ReleasedFunc)
			{
				BindAction(Action->InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action->InputTag);
			}
		}
	}
}
