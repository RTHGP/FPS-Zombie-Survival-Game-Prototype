// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	
	AMyGameMode();

	void BeginPlay() override;

	void Tick(float DeltaTime) override;

public:

	void EnemyReduce();

	UPROPERTY(BlueprintReadOnly)
		int32 Round;

private:
		
	UPROPERTY(EditAnywhere, Category = "GameSettings")
		TSubclassOf<AActor> EnemyClass; // BP_Enemy
	
	UPROPERTY(EditAnywhere, Category = "GameSettings")
		TSubclassOf<AActor> SpawnPoint; 
	
	UPROPERTY(EditAnywhere, Category = "GameSettings")
		int32 EnemyNumber;

	TArray<AActor*> ESpawnPoint;

	int32 NetEnemies;

	int32 TotalEnemies;

	int32 DeadEnemies;

	float TimeToSpawn;

	bool bCanEnemySpawn;

	UClass* Enemy;

	FActorSpawnParameters EnemySpawnParams;

	void SpawnEnemy();

};
