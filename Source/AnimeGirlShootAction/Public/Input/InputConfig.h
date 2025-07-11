#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "InputConfig.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FTaggedInputAction
{
	GENERATED_BODY()
	
public:
	FTaggedInputAction();

	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction;

	UPROPERTY(EditDefaultsOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};

UCLASS()
class ANIMEGIRLSHOOTACTION_API UInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	const UInputAction* FindInputActionByTag(const FGameplayTag& InputTag) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputAction"))
	TArray<FTaggedInputAction> TaggedInputActions;
};
