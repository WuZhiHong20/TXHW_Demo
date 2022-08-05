// Fill out your copyright notice in the Description page of Project Settings.


#include "SAICharacter.h"
#include "SWorkdUserWidget.h"

// Sets default values
ASAICharacter::ASAICharacter()
{	
	score = 10;
	MaxHealth = 3;
	CurrentHealth = 3;
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASAICharacter::BeginPlay()
{
	Super::BeginPlay();

	if (ActiveHealthBar == nullptr) {
		ActiveHealthBar = CreateWidget<USWorkdUserWidget>(GetWorld(), HealthBarWidgetClass);
		if (ActiveHealthBar) {
			ActiveHealthBar->AttachedActor = this;
			ActiveHealthBar->AddToViewport();
		}
	}
	
}

// Called every frame
void ASAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
