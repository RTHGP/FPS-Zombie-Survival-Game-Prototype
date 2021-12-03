// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MoveToPlayer.generated.h"

class AEnemy;
class ASPlayer;
/**
 * 
 */
UCLASS(Blueprintable)
class PROTOTYPE_API UMoveToPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UMoveToPlayer();

protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;

	void TickTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory, float DeltaTime) override;

private:

	FVector Direction;

	AEnemy* EnemyPawn;

	ASPlayer* MainPlayer;
};
