// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "GameFramework/Pawn.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "UObject/UObjectGlobals.h"
#include "FindRandomLocation.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROTOTYPE_API UFindRandomLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	UFindRandomLocation();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings", meta = (AllowProtectedAccess = "true"))
		float SearchRadius = 1500.f;
	
};
