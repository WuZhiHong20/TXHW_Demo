// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HWGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class HW_API UHWGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UHWGameInstance();
	UPROPERTY(BlueprintReadWrite)
		int32 pos;
	TArray<FString> levels;
	FString* getNextLevel();
	FString* getCurrentLevel();

	UPROPERTY(BlueprintReadWrite)
		int32 totalGoal;

	void addGoal(int32 num);

	UFUNCTION(BlueprintCallable)
		int32 getGoal();

	UFUNCTION(BlueprintCallable)
	void loadLevel(int32 levelPos);
};