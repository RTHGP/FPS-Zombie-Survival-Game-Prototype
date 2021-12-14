// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

class ASPlayer;
class AEnemy;

/**
 * 
 */
UCLASS()
class PROTOTYPE_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
public:
	AEnemyAIController();

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void OnPossess(APawn* pawn) override;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		class UBehaviorTree* BTree;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		class UBlackboardComponent* BBoard;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		class UBehaviorTreeComponent* BTreeComp;

private:

	void MoveToPlayer();

	float DeltaSeconds;
	
	bool bFindAngle;

	bool bIsJumped; // remove

	FVector Direction;

	AEnemy* Enemy;

	ASPlayer* MainPlayer;

public:
	FVector GetMainPlayerLocation();
};