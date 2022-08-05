// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "HWSaveGame.generated.h"

UCLASS()
class HW_API UHWSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	int32 levelPos;
	UPROPERTY(BlueprintReadWrite)
	int32 totalGoal;
};
