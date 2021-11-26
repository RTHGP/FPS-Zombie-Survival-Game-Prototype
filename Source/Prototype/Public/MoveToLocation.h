// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MoveToLocation.generated.h"

class AEnemy;
class UCharacterMovementComponent;
/**
 * 
 */
UCLASS(Blueprintable)
class PROTOTYPE_API UMoveToLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	
	UMoveToLocation();

protected:
		
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;
	
	void TickTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory, float DeltaTime) override;
private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = true))
		float MaxTimeToWalk = 2.f;

	float Delay;

	float Range;

	FVector Loc;

	FVector Direction;

	FVector EnemyLoc;

	AEnemy* EnemyPawn;

	void Move(FVector Dir);
};
