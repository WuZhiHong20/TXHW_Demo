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
		//���Set Visibility��UUserWidget�Դ���
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
bPauseһ��ʼ��false��ÿ�ε���GamePause������ȡ��
Ȼ�����void AHWPlayerController::SetPauseMenuVisibility(bool Visibility)����UI�Ƿ���ʾ
��������Ƿ���ʾ��Ȼ����Ϸ��ͣ
*/
void AHWPlayerController::GamePause() {
	bPause = !bPause;
	SetPauseMenuVisibility(bPause);
	bShowMouseCursor = bPause;
	UGameplayStatics::SetGamePaused(this, bPause);
}

/*
��GameInstance������ֺܷ͵�ǰ�ؿ�������Save Game����
*/
void AHWPlayerController::SaveGame() {
	UHWSaveGame* Instance = Cast<UHWSaveGame>(UGameplayStatics::CreateSaveGameObject(UHWSaveGame::StaticClass()));
	Instance->levelPos = GetGameInstance<UHWGameInstance>()->pos;
	Instance->totalGoal = GetGameInstance<UHWGameInstance>()->totalGoal;
	if (UGameplayStatics::SaveGameToSlot(Instance, TEXT("A"), 0)) {
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("SaveSuccessfully")));
	}
}

//��SaveGame������������¸�ֵ��GameInstance�����������Ӧ�Ĺؿ�
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