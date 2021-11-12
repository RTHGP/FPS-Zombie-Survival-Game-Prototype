// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MoveToLocation.generated.h"

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
		
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory);
	
};
