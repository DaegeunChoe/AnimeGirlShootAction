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
		AnimeGirlInputComponent->BindTaggedActions(
			AnimeGirlPlayerController->InputConfig,
			this,
			&AAnimeGirlCharacter::InputPressed,
			&AAnimeGirlCharacter::InputReleased);
	}
}

UAbilitySystemComponent* AAnimeGirlCharacter::GetAbilitySystemComponent() const
{
	return ASC;
}

void AAnimeGirlCharacter::InputPressed(const FInputActionValue& InputValue, FGameplayTag Tag)
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

void AAnimeGirlCharacter::InputReleased(const FInputActionValue& InputValue, FGameplayTag Tag)
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
