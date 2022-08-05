// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxActor.h"
#include "Components/BoxComponent.h"
#include "HWGameInstance.h"
#include "HWGameStateBase.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABoxActor::ABoxActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetBoxExtent(FVector(128, 128, 64));
	BoxComp->SetVisibility(true);
}

// Called when the game starts or when spawned
void ABoxActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoxActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoxActor::HandleDoorOpenEvent()
{
	OnDoorOpen.ExecuteIfBound();
}

void ABoxActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	HandleDoorOpenEvent();
}
void ABoxActor::NotifyActorEndOverlap(AActor* OtherActor) {
	goToNextLevel();
}

void ABoxActor::goToNextLevel()
{
	if (GetWorld()->GetGameState<AHWGameStateBase>()->bNextLevel()) {
		FString nextLevel = *GetGameInstance<UHWGameInstance>()->getNextLevel();
		UGameplayStatics::OpenLevel(GetWorld(), FName(nextLevel));
	}
}