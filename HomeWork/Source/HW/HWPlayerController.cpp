// Fill out your copyright notice in the Description page of Project Settings.

#include "Blueprint/UserWidget.h"
#include "HWSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "HWGameInstance.h"
#include "HWPlayerController.h"

void AHWPlayerController::BeginPlay() {

	bPause = false;
	Super::BeginPlay();
	if (HUDAsset) {
		HUD = CreateWidget<UUserWidget>(this, HUDAsset);
	}
	if (HUD) {
		HUD->AddToViewport();
	}



	if (PauseMenuAsset) {
		PauseMenu = CreateWidget<UUserWidget>(this, PauseMenuAsset);
	}

	if (PauseMenu) {
		//这个Set Visibility是UUserWidget自带的
		PauseMenu->SetVisibility(ESlateVisibility::Hidden);

		PauseMenu->AddToViewport();
	}
}

void AHWPlayerController::SetPauseMenuVisibility(bool Visibility) {
	if (PauseMenu) {
		if (Visibility) {
			PauseMenu->SetVisibility(ESlateVisibility::Visible);
		}
		else {
			PauseMenu->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

/*
bPause一开始是false，每次调用GamePause都将它取反
然后调用void AHWPlayerController::SetPauseMenuVisibility(bool Visibility)设置UI是否显示
设置鼠标是否显示，然后将游戏暂停
*/
void AHWPlayerController::GamePause() {
	bPause = !bPause;
	SetPauseMenuVisibility(bPause);
	bShowMouseCursor = bPause;
	UGameplayStatics::SetGamePaused(this, bPause);
}

/*
将GameInstance里面的总分和当前关卡坐标存进Save Game里面
*/
void AHWPlayerController::SaveGame() {
	UHWSaveGame* Instance = Cast<UHWSaveGame>(UGameplayStatics::CreateSaveGameObject(UHWSaveGame::StaticClass()));
	Instance->levelPos = GetGameInstance<UHWGameInstance>()->pos;
	Instance->totalGoal = GetGameInstance<UHWGameInstance>()->totalGoal;
	if (UGameplayStatics::SaveGameToSlot(Instance, TEXT("A"), 0)) {
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("SaveSuccessfully")));
	}
}

//将SaveGame里面的属性重新赋值给GameInstance，并进入相对应的关卡
void AHWPlayerController::LoadGame() {
	if (UHWSaveGame* Instance = Cast<UHWSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("A"), 0)))
	{
		GetGameInstance<UHWGameInstance>()->totalGoal = Instance->totalGoal;
		GetGameInstance<UHWGameInstance>()->pos = Instance->levelPos;
		GetGameInstance<UHWGameInstance>()->loadLevel(Instance->levelPos);
	}
}

void AHWPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();
	InputComponent->BindAction("Pause", IE_Pressed, this, &AHWPlayerController::GamePause);
}