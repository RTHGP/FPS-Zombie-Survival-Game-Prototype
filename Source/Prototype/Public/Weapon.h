// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class USkeletalMeshComponent;
class UStaticMesh;
class ABullet;

UCLASS()
class PROTOTYPE_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Settings")
	USkeletalMeshComponent* SKMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Fire();
	
	void Reload();

	float GetFireRate();

	void AddAmmo(int32 Ammo);

	UStaticMeshComponent* GetCurrentOptic();
	
	UPROPERTY(EditAnywhere, Category = "Weapon Settings")
	UStaticMeshComponent* CurrentOptic;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Settings")
	TArray<UStaticMesh*> Optics;	//use this array to cycle optics

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Weapon Settings")
		int32 MaxAmmo;

	UPROPERTY(BlueprintReadOnly)
		int32 AmmoLeft;

private:
	UPROPERTY(EditAnywhere, Category = "Weapon Settings")
		int32 MagCapacity;

	UPROPERTY(EditAnywhere, Category = "Weapon Settings")
		float FireRange = 10000.f;
	
	UPROPERTY(EditAnywhere, Category = "Weapon Settings")
		float FireRate = 10.f;

	UPROPERTY(EditAnywhere, Category = "Weapon Settings")
		float EnemyDamageAmount = 20.f;
	
	UPROPERTY(EditAnywhere, Category = "Weapon Settings")
		TSubclassOf<AActor> BulletClass;

	FHitResult BulletHit;

	FActorSpawnParameters BulletParams;

	ABullet* bullet;

	void AttachOptic();

};
