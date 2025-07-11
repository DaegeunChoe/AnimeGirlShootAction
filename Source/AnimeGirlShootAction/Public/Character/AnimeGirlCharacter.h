#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AnimeGirlCharacter.generated.h"

struct FInputActionValue;
struct FGameplayTag;

UCLASS()
class ANIMEGIRLSHOOTACTION_API AAnimeGirlCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAnimeGirlCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:
	void InputPressed(const FInputActionValue& InputValue, FGameplayTag tag);
	void InputReleased(const FInputActionValue& InputValue, FGameplayTag tag);
};
