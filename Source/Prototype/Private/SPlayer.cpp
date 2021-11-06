// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayer.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"
#include "HealthDamageComponent.h"
#include "MoveComponent.h"
#include "TimerManager.h"
#include "PlayerAnim.h"
#include "Weapon.h"

// Sets default values
ASPlayer::ASPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	RootComponent = CapsuleComp;
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(CapsuleComp);
	SKMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SKMeshComp"));
	SKMeshComp->SetupAttachment(CameraComp);
	HDComp = CreateDefaultSubobject<UHealthDamageComponent>(TEXT("HDComp"));
	MoveComp = CreateDefaultSubobject<UMoveComponent>(TEXT("MoveComp"));
}

// Called when the game starts or when spawned
void ASPlayer::BeginPlay()
{
	Super::BeginPlay();
	AnimInst = Cast<UPlayerAnim>(SKMeshComp->GetAnimInstance());
	HDComp->Health = PlayerHealth;
	AttachGun(WeaponClass);
}

// Called every frame
void ASPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DeltaSeconds = DeltaTime;

}

// Called to bind functionality to input
void ASPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ASPlayer::MoveForward);\
	PlayerInputComponent->BindAxis("MoveRight", this, &ASPlayer::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &ASPlayer::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ASPlayer::LookUp);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASPlayer::MakeJump);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASPlayer::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ASPlayer::StopFire);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ASPlayer::Reload);
	PlayerInputComponent->BindAction("ADS", IE_Pressed, this, &ASPlayer::StartAimDownSight);
	PlayerInputComponent->BindAction("ADS", IE_Released, this, &ASPlayer::StopAimDownSight);
}

void ASPlayer::AddAmmo(int32 Ammo)
{
	Gun->AddAmmo(Ammo);
}

float ASPlayer::GetPlayerHealth()
{
	return HDComp->Health;
}

void ASPlayer::DamageSelf(float DamageAmount)
{
	HDComp->Damage(DamageAmount);
}

AWeapon* ASPlayer::GetPlayerWeapon()
{
	return Gun;
}

USkeletalMeshComponent* ASPlayer::GetPlayerMesh()
{
	return SKMeshComp;
}

UCameraComponent* ASPlayer::GetCameraComponent()
{
	return CameraComp;
}

void ASPlayer::MoveForward(float Value)
{	
	Value = Value * MoveSpeed * DeltaSeconds;
	MoveComp->AddPlayerMovement(GetActorForwardVector(), Value);
}

void ASPlayer::MoveRight(float Value)
{
	Value = Value * SidewaySpeed * DeltaSeconds;
	MoveComp->AddPlayerMovement(GetActorRightVector(), Value);
}

void ASPlayer::Turn(float Value)
{	
	MouseX = Value* DeltaSeconds *MouseSpeed;
	FRotator Rot(0.f, MouseX, 0.f);
	MoveComp->AddPlayerRotation(Rot.Quaternion());
}

void ASPlayer::LookUp(float Value)
{	
	MouseY = Value * DeltaSeconds * MouseSpeed;
	ClampY += MouseY;
	if (ClampY > 90.f)
	{
		ClampY = 90.f;
		return;
	}
	else if (ClampY < -90.f)
	{
		ClampY = -90.f;
		return;
	}
	CameraComp->AddLocalRotation(FRotator(MouseY, 0.f, 0.f).Quaternion());
}

void ASPlayer::MakeJump()
{
	CapsuleComp->AddImpulse(FVector(0, 0, JumpSpeed)); // fix pending
}

void ASPlayer::Fire()
{	
	if (Gun)
	{	
		Gun->Fire();
	}
}

void ASPlayer::StartFire()
{
	GetWorld()->GetTimerManager().SetTimer(AutoFire, this, &ASPlayer::Fire, 1 / Gun->GetFireRate(), true, 0.f);
}

void ASPlayer::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(AutoFire);
}

void ASPlayer::Reload()
{
	if (Gun)
		Gun->Reload();
}

void ASPlayer::AttachGun(UClass* Weapon)
{	
	if (Weapon)
	{	
		Gun = GetWorld()->SpawnActor<AWeapon>(Weapon, FVector(0), FRotator(0));
		Gun->AttachToComponent(SKMeshComp, FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	}
}

void ASPlayer::StartAimDownSight()
{
	AnimInst->IsADS = 1;
	AnimInst->IsInterp = true;
}

void ASPlayer::StopAimDownSight()
{
	AnimInst->IsADS = 0;
	AnimInst->IsInterp = true;
}
