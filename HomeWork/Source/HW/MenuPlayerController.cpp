// Fill out your copyright notice in the Description page of Project Settings.

#include "Blueprint/UserWidget.h"
#include "MenuPlayerController.h"
#include "HWSaveGame.h"
#include "HWGameInstance.h"
#include "Kismet/GameplayStatics.h"

void AMenuPlayerController::BeginPlay() {
	Super::BeginPlay();
	if (HUDAsset) {
		HUD = CreateWidget<UUserWidget>(this, HUDAsset);
	}
	if (HUD) {
		HUD->AddToViewport();
	}

	bShowMouseCursor = true;
}

void AMenuPlayerController::LoadGame() {
	if (UHWSaveGame* Instance = Cast<UHWSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("A"), 0)))
	{
		GetGameInstance<UHWGameInstance>()->totalGoal = Instance->totalGoal;
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("totalGoal = %d"), Instance->totalGoal));
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("pos = %d"), Instance->levelPos));
		GetGameInstance<UHWGameInstance>()->pos = Instance->levelPos;
		GetGameInstance<UHWGameInstance>()->loadLevel(Instance->levelPos);
	}
}

void AMenuPlayerController::NewGame() {
	int8 pos = 0;
	GetGameInstance<UHWGameInstance>()->loadLevel(pos);
}