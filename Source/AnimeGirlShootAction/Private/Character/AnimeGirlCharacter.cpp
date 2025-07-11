#include "Character/AnimeGirlCharacter.h"


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
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
