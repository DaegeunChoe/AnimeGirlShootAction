#include "Character/AnimeGirlCharacter.h"
#include "Character/AnimeGirlPlayerController.h"
#include "Input/AnimeGirlEnhancedInputComponent.h"


AAnimeGirlCharacter::AAnimeGirlCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AAnimeGirlCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAnimeGirlCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAnimeGirlCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UAnimeGirlEnhancedInputComponent* AnimeGirlInputComponent = Cast<UAnimeGirlEnhancedInputComponent>(PlayerInputComponent);
	AAnimeGirlPlayerController* AnimeGirlPlayerController = Cast<AAnimeGirlPlayerController>(GetController());

	if (InputComponent && AnimeGirlPlayerController)
	{
		AnimeGirlInputComponent->BindTaggedActions(
			AnimeGirlPlayerController->InputConfig,
			this,
			&AAnimeGirlCharacter::InputPressed,
			&AAnimeGirlCharacter::InputReleased);
	}
}

void AAnimeGirlCharacter::InputPressed(const FInputActionValue& InputValue, FGameplayTag tag)
{
	FString Name = tag.GetTagName().ToString();
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue, FString::Printf(TEXT("Pressed: %s"), *Name));
}

void AAnimeGirlCharacter::InputReleased(const FInputActionValue& InputValue, FGameplayTag tag)
{
	FString Name = tag.GetTagName().ToString();
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue, FString::Printf(TEXT("Released: %s"), *Name));
}
