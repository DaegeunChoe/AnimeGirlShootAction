#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AnimeGirlPlayerController.generated.h"

class UInputMappingContext;
class UInputConfig;

UCLASS()
class ANIMEGIRLSHOOTACTION_API AAnimeGirlPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAnimeGirlPlayerController();
	virtual void BeginPlay();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> IMC_Default;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputConfig> InputConfig;
};
