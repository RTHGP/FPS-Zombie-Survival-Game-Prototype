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
}

EBTNodeResult::Type UMoveToLocation::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{	
	auto const cont = Cast<AEnemyAIController>(owner_comp.GetAIOwner());
	auto const enemyPawn = Cast<AEnemy>(cont->GetPawn());

	if (cont->bMTLTaskCompleted)
	{
		FVector Loc = cont->GetBlackboardComponent()->GetValueAsVector(TEXT("NewLocation"));
		cont->MoveToLocation(Loc);
		/*FVector Direction = Loc - enemyPawn->GetActorLocation();
		Direction.Normalize();*/
	
		/*while(enemyPawn->GetActorLocation() != Loc)
		enemyPawn->AddActorWorldOffset(Direction * enemyPawn->GetMoveSpeed() * GetWorld()->GetDeltaSeconds());*/

		FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
