#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySet.generated.h"

class UGameplayAbility;

USTRUCT(BlueprintType)
struct FTaggedAbility
{
	GENERATED_BODY()

public:
	FTaggedAbility();

	bool IsValid() const
	{
		return Ability != nullptr;
	}

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayAbility> Ability;

	UPROPERTY(EditDefaultsOnly)
	int32 AbilityLevel;

	UPROPERTY(EditDefaultsOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};


UCLASS()
class ANIMEGIRLSHOOTACTION_API UAbilitySet : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "Ability"))
	TArray<FTaggedAbility> TaggedAbilities;
};
