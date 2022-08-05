// Fill out your copyright notice in the Description page of Project Settings.

#include "HWCharacter.h"
#include "HWGameStateBase.h"
#include "MenuPlayerController.h"
#include "HWGameInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "MenuGameModeBase.h"

AMenuGameModeBase::AMenuGameModeBase() 
	: Super() 
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	GameStateClass = AHWGameStateBase::StaticClass();
	PlayerControllerClass = AMenuPlayerController::StaticClass();
}