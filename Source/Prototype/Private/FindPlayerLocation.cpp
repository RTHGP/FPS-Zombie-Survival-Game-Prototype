// Fill out your copyright notice in the Description page of Project Settings.


#include "FindPlayerLocation.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAIController.h"
#include "SPlayer.h"

UFindPlayerLocation::UFindPlayerLocation()
{
	NodeName = TEXT("FindPlayerLocation");
}

EBTNodeResult::Type UFindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{	
	Super::ExecuteTask(owner_comp, node_memory);
	auto const cont = Cast<AEnemyAIController>(owner_comp.GetAIOwner());
	ASPlayer* MainPlayer = cont->GetMainPlayer();
	cont->GetBlackboardComponent()->SetValueAsVector(TEXT("NewLocation"), MainPlayer->GetActorLocation());

	return EBTNodeResult::Succeeded;
}
