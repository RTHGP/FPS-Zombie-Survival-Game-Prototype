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

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	if (BTree)
	{
		RunBehaviorTree(BTree);
		BTreeComp->StartTree(*BTree);
	}
	bFindAngle = true;
	bIsJumped = false;
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DeltaSeconds += DeltaTime;
	Delay += DeltaTime;

	if(Delay >1.f)
	MoveToPlayer();
}

void AEnemyAIController::OnPossess(APawn* pawn)
{	
	Super::OnPossess(pawn);
	if (Blackboard)
	{
		Blackboard->InitializeBlackboard(*BTree->BlackboardAsset);
	}
}

void AEnemyAIController::MoveToPlayer()
{	
	AEnemy* Enemy = Cast<AEnemy>(GetPawn());
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
				//UE_LOG(LogTemp, Warning, TEXT("%f"), Angle);
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