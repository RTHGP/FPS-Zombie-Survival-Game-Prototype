// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveToPlayer.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAIController.h"
#include "SPlayer.h"
#include "Enemy.h"

UMoveToPlayer::UMoveToPlayer()
{
	NodeName = TEXT("MoveToPlayer");
}

EBTNodeResult::Type UMoveToPlayer::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	Super::ExecuteTask(owner_comp, node_memory);
	auto const cont = Cast<AEnemyAIController>(owner_comp.GetAIOwner());
	EnemyPawn = Cast<AEnemy>(cont->GetPawn());
	MainPlayer = cont->GetMainPlayer();

	

	return EBTNodeResult::InProgress;
}

void UMoveToPlayer::TickTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory, float DeltaTime)
{
	Super::TickTask(owner_comp, node_memory, DeltaTime);

	FVector ELoc = EnemyPawn->GetActorLocation();
	FVector PLoc = MainPlayer->GetActorLocation();

	Direction = PLoc - ELoc;
	Direction.Normalize();
	EnemyPawn->SetActorRotation(Direction.Rotation().Quaternion());

	EnemyPawn->AddActorWorldOffset(Direction * EnemyPawn->GetMoveSpeed() * DeltaTime, true);
	if (EnemyPawn->GetActorLocation() == MainPlayer->GetActorLocation())
		FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
}
