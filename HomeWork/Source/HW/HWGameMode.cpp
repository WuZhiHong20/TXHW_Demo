// Copyright Epic Games, Inc. All Rights Reserved.

#include "HWGameMode.h"
#include "HWHUD.h"
#include "HWCharacter.h"
#include "HWGameStateBase.h"
#include "HWPlayerController.h"
#include "HWGameInstance.h"
#include "UObject/ConstructorHelpers.h"

AHWGameMode::AHWGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AHWHUD::StaticClass();
	GameStateClass = AHWGameStateBase::StaticClass();
	PlayerControllerClass = AHWPlayerController::StaticClass();
}

/*void AHWGameMode::StartPlay() {
	Super::StartPlay();	
}
*/
