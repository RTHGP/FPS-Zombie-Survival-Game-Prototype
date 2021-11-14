// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveToLocation.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAIController.h"
#include "Enemy.h"

UMoveToLocation::UMoveToLocation()
{
	NodeName = TEXT("MoveToLocation");
	bNotifyTick = true;
}

EBTNodeResult::Type UMoveToLocation::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{	
	Super::ExecuteTask(owner_comp, node_memory);
	auto const cont = Cast<AEnemyAIController>(owner_comp.GetAIOwner());
	EnemyPawn = Cast<AEnemy>(cont->GetPawn());

	Loc = cont->GetBlackboardComponent()->GetValueAsVector(TEXT("NewLocation"));
	EnemyLoc = EnemyPawn->GetActorLocation();

	Direction = Loc - EnemyLoc;
	Direction.Normalize();
	EnemyPawn->SetActorRotation(Direction.Rotation().Quaternion());

	return EBTNodeResult::InProgress;
}

void UMoveToLocation::TickTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory, float DeltaTime)
{
	Super::TickTask(owner_comp, node_memory, DeltaTime);
	Delay += DeltaTime;
	if (Delay < 2.f)
		EnemyPawn->AddActorWorldOffset(Direction * EnemyPawn->GetMoveSpeed() * DeltaTime);
	else
	{
		Delay = 0.f;
		FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	}
}
