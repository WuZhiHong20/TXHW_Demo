// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HWPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HW_API AHWPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UUserWidget> HUDAsset;

	UUserWidget* HUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UUserWidget> PauseMenuAsset;

	UUserWidget* PauseMenu;

	UFUNCTION(BlueprintCallable)
		void SaveGame();

	UFUNCTION(BlueprintCallable)
		void LoadGame();

	UFUNCTION(BlueprintCallable)
		void GamePause();

	

	void SetPauseMenuVisibility(bool Visibility);

	bool bPause;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;
};
