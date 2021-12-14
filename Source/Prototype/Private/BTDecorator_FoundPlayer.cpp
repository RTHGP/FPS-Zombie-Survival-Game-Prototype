// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_FoundPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UBTDecorator_FoundPlayer::CalculateRawConditionValue(UBehaviorTreeComponent& owner_comp, uint8* node_memory) const
{	
	UBlackboardComponent* BlackboardComp = owner_comp.GetBlackboardComponent();
	if (!BlackboardComp)
		return false;

	return BlackboardComp->GetValueAsBool(BoolKey.SelectedKeyName);
}

FString UBTDecorator_FoundPlayer::GetStaticDescription() const
{
	return FString::Printf(TEXT("BoolKey:'%s'"), BoolKey.IsSet() ? *BoolKey.SelectedKeyName.ToString() : TEXT(""));
}
