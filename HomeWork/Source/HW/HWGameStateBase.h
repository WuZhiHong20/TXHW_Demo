// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "HWGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class HW_API AHWGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
private:
	int32 totalScore;
	bool enterNextLevel;
	int32 scoreNeeded;
public:
	
	AHWGameStateBase();
	
	void addScore(int32 score);
	bool bNextLevel();
	void setScoreNeeded(int32 num);

	UFUNCTION(BlueprintCallable)
		int32 getScore();
	UFUNCTION(BlueprintCallable)
		int32 getScoreNeeded();
};
