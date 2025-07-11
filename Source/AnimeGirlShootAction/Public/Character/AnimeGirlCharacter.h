#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AnimeGirlCharacter.generated.h"

class UAbilitySet;
struct FInputActionValue;
struct FGameplayTag;

UCLASS()
class ANIMEGIRLSHOOTACTION_API AAnimeGirlCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAnimeGirlCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// GAS
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UAbilitySystemComponent> ASC;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UAbilitySet> DefaultAbilitySet;

private:
	void InputPressed(const FInputActionValue& InputValue, FGameplayTag Tag);
	void InputReleased(const FInputActionValue& InputValue, FGameplayTag Tag);
};
