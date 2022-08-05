// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoxActor.generated.h"


DECLARE_DELEGATE(FOnDoorOpenDelegate);
UCLASS()
class HW_API ABoxActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoxActor();
	void goToNextLevel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION()
		void HandleDoorOpenEvent();
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		class UBoxComponent* BoxComp;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor);
	virtual void NotifyActorEndOverlap(AActor* OtherActor);

public:
	FOnDoorOpenDelegate OnDoorOpen;

};
