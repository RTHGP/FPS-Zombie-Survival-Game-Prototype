// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Enemy.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;
class USphereComponent;
class UHealthDamageComponent;

UCLASS()
class PROTOTYPE_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	bool bIsNearPlayer; //test

	bool bIsStuck; //test

	bool bFoundPlayer; //test

	float FollowPlayerTime; // test

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void DamageSelf(float DamageAmount);

	float GetMoveSpeed();

	float GetStopingDistance();

	float GetPlayerDamageAmount();

	void MakeJump();

	void DropAmmo();

private:
	UPROPERTY(EditDefaultsOnly, Category = "EnemySettings")
		UCapsuleComponent* CapsuleComp;

	UPROPERTY(EditDefaultsOnly, Category = "EnemySettings")
		UHealthDamageComponent* HDComp;

	UPROPERTY(EditDefaultsOnly, Category = "EnemySettings")
		UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "EnemySettings")
		USphereComponent* SphereComp; // to detect player

	UPROPERTY(EditDefaultsOnly, Category = "EnemySettings")
		float Health = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = "EnemySettings")
		float PlayerDamageAmount = 20.f;

	UPROPERTY(EditDefaultsOnly, Category = "EnemySettings")
		float MoveSpeed = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = "EnemySettings")
		float JumpSpeed = 25000.f;

	UPROPERTY(EditDefaultsOnly, Category = "EnemySettings")
		float StopingDistance = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = "EnemySettings")
		float RayHeight = 70.f; //

	UPROPERTY(EditDefaultsOnly, Category = "EnemySettings")
		TSubclassOf<AActor> AmmoDrop;

	UFUNCTION()
		void BeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

	UFUNCTION()
		void BeginOverlap2(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EndOverlap2(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

};