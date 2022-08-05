// Fill out your copyright notice in the Description page of Project Settings.


#include "HWGameStateBase.h"

AHWGameStateBase::AHWGameStateBase() {
	totalScore = 0;
	enterNextLevel = false;	
}

int32 AHWGameStateBase::getScore() {
	return totalScore;
}

void AHWGameStateBase::addScore(int32 score) {
	totalScore += score;
	if (totalScore >= scoreNeeded) enterNextLevel = true;
}

bool AHWGameStateBase::bNextLevel() {
	return enterNextLevel;
}


void AHWGameStateBase::setScoreNeeded(int32 num) {
	scoreNeeded = num;
}

int32 AHWGameStateBase::getScoreNeeded() {
	return scoreNeeded;
}

