// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToPlayer.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAIController.h"
#include "SPlayer.h"
#include "Enemy.h"

UBTTask_MoveToPlayer::UBTTask_MoveToPlayer()
{
	NodeName = TEXT("MoveToPlayer");
}

EBTNodeResult::Type UBTTask_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{		
	Super::ExecuteTask(owner_comp, node_memory);

	auto cont = Cast<AEnemyAIController>(owner_comp.GetAIOwner());
	Enemy = Cast<AEnemy>(cont->GetPawn());
	//BlackboardComp = cont->GetBlackboardComponent();
	//Player = Cast<ASPlayer>(BlackboardComp->GetValueAsClass("Player"));

	FVector EnemyLoc = Enemy->GetActorLocation();
	FVector PlayerLoc = cont->GetMainPlayerLocation();//Player->GetActorLocation();
	FVector Direction = PlayerLoc - EnemyLoc;
	Direction.Normalize();
	
	Enemy->AddActorWorldOffset(Direction * Enemy->GetMoveSpeed() * GetWorld()->GetDeltaSeconds(), true);

	return EBTNodeResult::Succeeded;
}

//void UBTTask_MoveToPlayer::TickTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory, float DeltaTime)
//{
//	Super::TickTask(owner_comp, node_memory, DeltaTime);
//
//	Player = Cast<ASPlayer>(BlackboardComp->GetValueAsClass("Player"));
//
//	FVector EnemyLoc = Enemy->GetActorLocation();
//	FVector PlayerLoc = Player->GetActorLocation();
//	FVector Direction = PlayerLoc - EnemyLoc;
//	Direction.Normalize();
//
//	Enemy->AddActorWorldOffset(Direction * Enemy->GetMoveSpeed() * DeltaTime, true);
//
//	if (Direction.Size() < 1)
//		FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
//	else
//		FinishLatentTask(owner_comp, EBTNodeResult::InProgress);
//
//}

FString UBTTask_MoveToPlayer::GetStaticDescription() const
{
	return FString::Printf(TEXT("%s: '%s'"), TEXT("PlayerKey"), PlayerKey.IsSet() ? *PlayerKey.SelectedKeyName.ToString() : TEXT(""));
}
