#include "Character/AnimeGirlCharacter.h"
#include "Character/AnimeGirlPlayerController.h"
#include "Input/AnimeGirlEnhancedInputComponent.h"
#include "AbilitySystemComponent.h"
#include "Ability/AbilitySet.h"
#include "Abilities/GameplayAbility.h"

AAnimeGirlCharacter::AAnimeGirlCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
}

void AAnimeGirlCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (DefaultAbilitySet)
	{
		for (auto& Ability : DefaultAbilitySet->TaggedAbilities)
		{
			if (Ability.Ability && Ability.InputTag.IsValid())
			{
				FGameplayAbilitySpec AbilitySpec(Ability.Ability);
				ASC->GiveAbility(AbilitySpec);
			}
		}
	}
}

void AAnimeGirlCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAnimeGirlCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UAnimeGirlEnhancedInputComponent* AnimeGirlInputComponent = Cast<UAnimeGirlEnhancedInputComponent>(PlayerInputComponent);
	AAnimeGirlPlayerController* AnimeGirlPlayerController = Cast<AAnimeGirlPlayerController>(GetController());

	if (AnimeGirlInputComponent && AnimeGirlPlayerController)
	{
		if (UInputConfig* InputConfig = AnimeGirlPlayerController->InputConfig)
		{
			// Abilities
			AnimeGirlInputComponent->BindTaggedActions(InputConfig, this, &AAnimeGirlCharacter::InputPressed, &AAnimeGirlCharacter::InputReleased);

			// NativeActions
			if (auto MoveAction = InputConfig->MoveAction; MoveAction.IsValid())
			{
				AnimeGirlInputComponent->BindAction(MoveAction.InputAction, ETriggerEvent::Triggered, this, &AAnimeGirlCharacter::CharacterMove, MoveAction.InputTag);
			}
			if (auto LookAction = InputConfig->LookAction; LookAction.IsValid())
			{
				AnimeGirlInputComponent->BindAction(LookAction.InputAction, ETriggerEvent::Triggered, this, &AAnimeGirlCharacter::CharacterLook, LookAction.InputTag);
			}
		}
	}
}

UAbilitySystemComponent* AAnimeGirlCharacter::GetAbilitySystemComponent() const
{
	return ASC;
}

void AAnimeGirlCharacter::CharacterMove(const FInputActionValue& InputValue, FGameplayTag Tag)
{
	FVector2D MoveVector = InputValue.Get<FVector2D>();
	if (!MoveVector.IsNearlyZero())
	{
		FVector ForwardVector = GetActorForwardVector() * MoveVector.X;
		FVector RightVector = GetActorRightVector() * MoveVector.Y;
		AddMovementInput(ForwardVector + RightVector);
	}
}

void AAnimeGirlCharacter::CharacterLook(const FInputActionValue& InputValue, FGameplayTag Tag)
{
	FVector2D LookVector = InputValue.Get<FVector2D>();
	if (!LookVector.IsNearlyZero())
	{
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
}

void AAnimeGirlCharacter::InputPressed(FGameplayTag Tag)
{
	//FString Name = Tag.GetTagName().ToString();
	//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue, FString::Printf(TEXT("Pressed: %s"), *Name));
	
	if (DefaultAbilitySet)
	{
		for (auto& Pair : DefaultAbilitySet->TaggedAbilities)
		{
			if (Pair.InputTag.IsValid() && Pair.InputTag.MatchesTagExact(Tag))
			{
				if (Pair.Ability)
				{
					FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromClass(Pair.Ability);
					ASC->TryActivateAbility(Spec->Handle);
				}
			}
		}
	}
}

void AAnimeGirlCharacter::InputReleased(FGameplayTag Tag)
{
	//FString Name = Tag.GetTagName().ToString();
	//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue, FString::Printf(TEXT("Released: %s"), *Name));

	if (DefaultAbilitySet)
	{
		for (auto& Pair : DefaultAbilitySet->TaggedAbilities)
		{
			if (Pair.InputTag.IsValid() && Pair.InputTag.MatchesTagExact(Tag))
			{
				if (Pair.Ability)
				{
					FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromClass(Pair.Ability);
					ASC->CancelAbilityHandle(Spec->Handle);
				}
			}
		}
	}
}
