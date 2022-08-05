// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HW_API AMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UUserWidget> HUDAsset;

	UUserWidget* HUD;

	UFUNCTION(BlueprintCallable)
		void NewGame();

	UFUNCTION(BlueprintCallable)
		void LoadGame();
protected:
	virtual void BeginPlay() override;
};
