// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon.h"
#include "Enemy.h"

AMyGameMode::AMyGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();
	NetEnemies = 0;
	TotalEnemies = EnemyNumber;
	Enemy = EnemyClass;
	EnemySpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), SpawnPoint, ESpawnPoint);

	if(ESpawnPoint.Num())
		bCanEnemySpawn = true;
	else
		UE_LOG(LogTemp, Warning, TEXT("No Spawn Points!!"));
}

void AMyGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bCanEnemySpawn)
	{
		TimeToSpawn += DeltaTime;
		if (NetEnemies < TotalEnemies)
		{	
			if (TimeToSpawn >= 0.8f && TotalEnemies > 0)
			{
				SpawnEnemy();
				TimeToSpawn = 0.f;
			}
		}
		else
		{
			bCanEnemySpawn = false;
			TimeToSpawn = 0.f;
		}
	}
	
}

void AMyGameMode::EnemyReduce()
{
	DeadEnemies++;
	//UE_LOG(LogTemp, Warning, TEXT("%d"), DeadEnemies);
	if (DeadEnemies == TotalEnemies)
	{	
		Round++;
		EnemyNumber *= 2;
		TotalEnemies = EnemyNumber;
		NetEnemies = 0;
		DeadEnemies = 0;
		bCanEnemySpawn = true;
	}
}

void AMyGameMode::SpawnEnemy()
{
	int32 index = FMath::RandRange(0, ESpawnPoint.Num() - 1);
	FVector SpawnLocation = ESpawnPoint[index]->GetActorLocation();
	FRotator SpawnRotation = ESpawnPoint[index]->GetActorRotation();
	GetWorld()->SpawnActor<AEnemy>(Enemy, SpawnLocation, SpawnRotation, EnemySpawnParams);
	NetEnemies++;
}
