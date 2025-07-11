#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AbilitySet.generated.h"

class UGameplayAbility;

USTRUCT(BlueprintType)
struct FTaggedAbility
{
	GENERATED_BODY()

public:
	FTaggedAbility();

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
	TSubclassOf<UGameplayAbility> FindAbilityClassByTag(const FGameplayTag& InputTag) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "Ability"))
	TArray<FTaggedAbility> TaggedAbilities;
};
