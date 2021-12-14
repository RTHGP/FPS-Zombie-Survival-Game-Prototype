// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BTTask_MoveToPlayer.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROTOTYPE_API UBTTask_MoveToPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_MoveToPlayer();
protected:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
		FBlackboardKeySelector PlayerKey;
	
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;

	//void TickTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory, float DeltaTime) override;

	FString GetStaticDescription() const override;

private:

	class AEnemy* Enemy;

	class ASPlayer* Player;

	class UBlackboardComponent* BlackboardComp;
};
