// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SPlayer.generated.h"

class USKeletalMeshComponent;
class UHealthDamageComponent;
class UCapsuleComponent;
class UCameraComponent;
class UMoveComponent;
class UPlayerAnim;
class AWeapon;

UCLASS()
class PROTOTYPE_API ASPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASPlayer();

	UPROPERTY(EditAnywhere, Category = "Player Settings")
	float PlayerHealth;

	UPROPERTY(EditAnywhere, Category = "Player Settings")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, Category = "Player Settings")
	float SidewaySpeed;

	UPROPERTY(EditAnywhere, Category = "Player Settings")
	float JumpSpeed;

	UPROPERTY(EditAnywhere, Category = "Player Settings")
	float MouseSpeed;

	UPROPERTY(EditAnywhere, Category = "Player Settings")
	TSubclassOf<AActor> WeaponClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Player Settings")
	UCapsuleComponent* CapsuleComp;

	UPROPERTY(EditDefaultsOnly, Category = "Player Settings")
	USkeletalMeshComponent* SKMeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "Player Settings")
	UCameraComponent* CameraComp;

	UPROPERTY(EditDefaultsOnly)
	UHealthDamageComponent* HDComp;
	
	UPROPERTY(EditDefaultsOnly)
	UMoveComponent* MoveComp;

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void AddAmmo(int32 Ammo);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetPlayerHealth();

	void DamageSelf(float DamageAmount);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	AWeapon* GetPlayerWeapon();

	USkeletalMeshComponent* GetPlayerMesh();

	UCameraComponent* GetCameraComponent();

private:

	float ClampY;

	float DeltaSeconds;

	float MouseX;

	float MouseY;

	AWeapon* Gun;

	UPlayerAnim* AnimInst;

	FTimerHandle AutoFire; 

	void MoveForward(float Value);

	void MoveRight(float Value);

	void Turn(float Value);

	void LookUp(float Value);

	void MakeJump();

	void Fire();

	void StartFire();

	void StopFire();

	void Reload();

	void AttachGun(UClass* Weapon);

	void StartAimDownSight();

	void StopAimDownSight();

};
