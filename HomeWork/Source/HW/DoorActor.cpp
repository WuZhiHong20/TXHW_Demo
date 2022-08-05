// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorActor.h"
#include "BoxActor.h"
#include "HWGameStateBase.h"

// Sets default values
ADoorActor::ADoorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrameMesh"));
    Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
    DoorTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimelineComp"));

    //设置绑定
    DoorFrame->SetupAttachment(RootComponent);
    Door->AttachToComponent(DoorFrame, FAttachmentTransformRules::KeepRelativeTransform);
    Door->SetRelativeLocation(FVector(0, 35, 0));
}

// Called when the game starts or when spawned
void ADoorActor::BeginPlay()
{
	Super::BeginPlay();

    //将浮点轨道绑定到UpdateTimelineComp函数的输出
    UpdateFunctionFloat.BindDynamic(this, &ADoorActor::UpdateTimelineComp);

    //如果有浮点曲线，将其图表绑定到我们的更新函数
    if (DoorTimelineFloatCurve)
    {
        DoorTimelineComp->AddInterpFloat(DoorTimelineFloatCurve, UpdateFunctionFloat);
    }

    if (BoxActorReference)
    {
        BoxActorReference->OnDoorOpen.BindUObject(this, &ADoorActor::DoorOpenEventFunction);
    }

    setTargetScore();
}

// Called every frame
void ADoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoorActor::DoorOpenEventFunction()
{
    if (GetWorld()->GetGameState<AHWGameStateBase>()->bNextLevel()) {
        DoorTimelineComp->Play();
        
    }
}

void ADoorActor::setTargetScore() {
    if(GetWorld()) GetWorld()->GetAuthGameMode()->GetGameState<AHWGameStateBase>()->setScoreNeeded(targetScore);
}



void ADoorActor::UpdateTimelineComp(float Output)
{
    // 基于时间轴曲线的输出，创建并设置门的新相对位置
    FRotator DoorNewRotation = FRotator(0.0f, Output, 0.f);
    Door->SetRelativeRotation(DoorNewRotation);
}

