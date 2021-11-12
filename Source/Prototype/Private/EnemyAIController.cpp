// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Enemy.h"
#include "SPlayer.h"
#include "Misc/App.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

AEnemyAIController::AEnemyAIController()
{
	PrimaryActorTick.bCanEverTick = true;
	BBoard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoard"));
	BTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
}

void AEnemyAIController::MoveToLocation(FVector Location)
{	
	bMTLTaskCompleted = false;
	FVector direction = Location - Enemy->GetActorLocation();
	direction.Normalize();

	if (Enemy->GetActorLocation() != Location)
		Enemy->AddActorWorldOffset(direction * Enemy->GetMoveSpeed() * DeltaSeconds);
	else
		bMTLTaskCompleted = true;
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	if (BTree)
	{
		bMTLTaskCompleted = true;
		RunBehaviorTree(BTree);
		BTreeComp->StartTree(*BTree);
	}
	bFindAngle = true;
	bIsJumped = false;

}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DeltaSeconds = DeltaTime;
	
	/*if (Enemy->bFoundPlayer)
	{
		Enemy->FollowPlayerTime += DeltaTime;
		MoveToPlayer();
	}*/
}

void AEnemyAIController::OnPossess(APawn* pawn)
{	
	Super::OnPossess(pawn);
	if (Blackboard)
	{
		Blackboard->InitializeBlackboard(*BTree->BlackboardAsset);
	}
	Enemy = Cast<AEnemy>(GetPawn());
	if (Enemy)
		UE_LOG(LogTemp, Warning, TEXT("ENemy Work!"));
}

void AEnemyAIController::MoveToPlayer()
{	
	ASPlayer* MainPlayer = Cast<ASPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (Enemy && MainPlayer)
	{	
		FVector EnemyPosition = Enemy->GetActorLocation();
		FVector PlayerPosition = MainPlayer->GetActorLocation();
		
		if (Enemy->bIsStuck) 
		{	
			if (bFindAngle)
			{	
				FVector LocalRightVector = Enemy->GetActorRightVector();
				DeltaSeconds = 0.f;
				Direction = PlayerPosition - EnemyPosition;
				auto Angle = FVector::DotProduct(Direction, LocalRightVector);
				if (Angle >= 0.f)
				{
					Direction = LocalRightVector;
				}
				else
				{
					Direction = -LocalRightVector;
				}
				Direction.Normalize();
				bFindAngle = false;
			}
			Enemy->SetActorRotation(Direction.Rotation().Quaternion());
			Enemy->AddActorWorldOffset(Direction * Enemy->GetMoveSpeed() * FApp::GetDeltaTime());
			if (DeltaSeconds > 1.f)
				Enemy->bIsStuck = false;
		}
		
		if(!Enemy->bIsNearPlayer && !Enemy->bIsStuck)
		{	
			Direction = PlayerPosition - EnemyPosition;
			Direction.Normalize();
			Direction.Z = 0.f;

			bFindAngle = true;
			Enemy->SetActorRotation(Direction.Rotation().Quaternion());
			Enemy->AddActorWorldOffset(Direction * Enemy->GetMoveSpeed() * FApp::GetDeltaTime());
		}
		if (Enemy->bIsNearPlayer && DeltaSeconds >= 1.f)
		{	
			MainPlayer->DamageSelf(Enemy->GetPlayerDamageAmount());
			DeltaSeconds = 0.f;
		}
	}
}