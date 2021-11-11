// Fill out your copyright notice in the Description page of Project Settings.


#include "FindRandomLocation.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "UObject/UObjectGlobals.h"
#include "EnemyAIController.h"

UFindRandomLocation::UFindRandomLocation(FObjectInitializer const& object_initializer)
{
	SearchRadius = 2000.f;
}


EBTNodeResult::Type UFindRandomLocation::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{	
	auto const cont = Cast<AEnemyAIController>(owner_comp.GetAIOwner());
	auto const enemyPawn = cont->GetPawn();


	return EBTNodeResult::Type();
}
