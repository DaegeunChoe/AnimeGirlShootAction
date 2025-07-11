#include "Character/AnimeGirlPlayerController.h"
#include "EnhancedInputSubsystems.h" 

AAnimeGirlPlayerController::AAnimeGirlPlayerController()
{
	IMC_Default = nullptr;
	InputConfig = nullptr;
}

void AAnimeGirlPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (ULocalPlayer* LP = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (IMC_Default)
			{
				int32 Priority = 0;
				Subsystem->AddMappingContext(IMC_Default, Priority);
			}
		}
	}
}
