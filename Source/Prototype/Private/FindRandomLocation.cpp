// Fill out your copyright notice in the Description page of Project Settings.


#include "FindRandomLocation.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAIController.h"

UFindRandomLocation::UFindRandomLocation()
{
	NodeName = TEXT("FindRandomLocation");
	SearchRadius = 3000.f;
}


EBTNodeResult::Type UFindRandomLocation::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{	
	auto const cont = Cast<AEnemyAIController>(owner_comp.GetAIOwner());
	auto const enemyPawn = cont->GetPawn();

	float X = FMath::RandRange(-SearchRadius, SearchRadius);
	float Y = FMath::RandRange(-SearchRadius, SearchRadius);

	if (cont->bMTLTaskCompleted)
	{
		FVector NewLoc = enemyPawn->GetActorLocation() + FVector(X, Y, 0);

		cont->GetBlackboardComponent()->SetValueAsVector(TEXT("NewLocation"), NewLoc);
	
		FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	EBTNodeResult::Failed;
}
