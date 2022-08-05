// Fill out your copyright notice in the Description page of Project Settings.


#include "SBTService_CheckAttackRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

void USBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//检查AI与MyPawn之间的距离
	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackBoardComp)) {
		AActor* TargetActor = Cast<AActor>(BlackBoardComp->GetValueAsObject("TargetActor"));

		if (TargetActor) {
			AAIController* MyController = OwnerComp.GetAIOwner();
			if (ensure(MyController)) {
				APawn* AIPawn = MyController->GetPawn();
				if (ensure(AIPawn)) {
					float DistanceBetween = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());

					bool bWithinRange = DistanceBetween < 1000.0f;

					bool bHasLOS = false;
					if (bWithinRange) {
						bHasLOS = MyController->LineOfSightTo(TargetActor);
					}

					BlackBoardComp->SetValueAsBool(AttackRangeKey.SelectedKeyName, bWithinRange&&bHasLOS);
				}
			}
		}
	}
}