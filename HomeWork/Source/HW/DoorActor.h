// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "DoorActor.generated.h"

UCLASS()
class HW_API ADoorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    // ���ڱ��������ʲ��ı���
    UPROPERTY(EditInstanceOnly)
        UCurveFloat* DoorTimelineFloatCurve;

protected:

    void DoorOpenEventFunction();
    UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
        class ABoxActor* BoxActorReference;

    //��ʾ�ŵ����������
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
        UStaticMeshComponent* DoorFrame;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
        UStaticMeshComponent* Door;

    //���ڶ�����������ж��������ʱ�������
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
        UTimelineComponent* DoorTimelineComp;

    //���ڴ������ǵĸ��¹���¼��ĸ�����ǩ��
    FOnTimelineFloat UpdateFunctionFloat;

    //����ʹ��ʱ����ͼ����������λ�õĺ���
    UFUNCTION()
        void UpdateTimelineComp(float Output);

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32 targetScore;

    void setTargetScore();
};
