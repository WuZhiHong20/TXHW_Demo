// Fill out your copyright notice in the Description page of Project Settings.

#include "HWGameInstance.h"
#include "Kismet/GameplayStatics.h"

UHWGameInstance::UHWGameInstance() {
	pos = 0;
	totalGoal = 0;
	levels.Add("Level_00");
	levels.Add("Level_01");
	levels.Add("Level_02");
	levels.Add("Menu");
}

FString* UHWGameInstance::getNextLevel() {
	++pos;
	if (pos == 3) {
		pos = 0;
		totalGoal = 0;
		return &levels[3];
	}
	return &levels[pos];
}

void UHWGameInstance::addGoal(int32 num) {
	totalGoal += num;
}

int32 UHWGameInstance::getGoal() {
	return totalGoal;
}

FString* UHWGameInstance::getCurrentLevel() {
	return &levels[pos];
}

void UHWGameInstance::loadLevel(int32 levelPos) {
	UGameplayStatics::OpenLevel(GetWorld(), FName(levels[levelPos]));
}