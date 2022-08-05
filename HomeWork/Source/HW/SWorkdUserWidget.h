// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SWorkdUserWidget.generated.h"

/**
 * 
 */
class USizeBox;

UCLASS()
class HW_API USWorkdUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:

	UPROPERTY(meta = (BindWidget))
		USizeBox* ParentSizeBox;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
public:
	UPROPERTY(BlueprintReadOnly, Category = "UI")
		AActor* AttachedActor; 
};
