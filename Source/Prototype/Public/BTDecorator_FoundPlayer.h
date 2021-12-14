// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BTDecorator_FoundPlayer.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROTOTYPE_API UBTDecorator_FoundPlayer : public UBTDecorator
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Blackboard")
		FBlackboardKeySelector BoolKey;
	
	bool CalculateRawConditionValue(UBehaviorTreeComponent& owner_comp, uint8* node_memory) const override;

	FString GetStaticDescription() const override;
};
