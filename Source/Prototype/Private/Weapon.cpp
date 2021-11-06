// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "Engine/StaticMesh.h"
#include "DrawDebugHelpers.h"
#include "Bullet.h"
#include "Enemy.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SKMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SKMesh"));
	RootComponent = SKMesh;
	CurrentOptic = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Optic"));
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	AmmoLeft = MagCapacity;
	BulletParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	if (Optics.Num())
	{
		CurrentOptic->SetStaticMesh(Optics[0]);
		AttachOptic();
	}
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AWeapon::Fire()
{	
	if (AmmoLeft)
	{
		FHitResult Hit;
		FVector Start = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation();
		FVector End = Start + GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetActorForwardVector() * FireRange;
		
		FVector Loc = SKMesh->GetSocketLocation(FName("S_Muzzle"));
		FRotator Rot = (End - SKMesh->GetSocketLocation(FName("S_Muzzle"))).Rotation();
		
		if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Camera))
		{	
			/*UE_LOG(LogTemp, Warning, TEXT("%s"), *Hit.GetActor()->GetName());
			auto Enemy = Cast<AEnemy>(Hit.GetActor());
			if (Enemy)
			{
				Enemy->DamageSelf(EnemyDamageAmount);
			}*/
			BulletHit = Hit;
			Rot = (Hit.Location - SKMesh->GetSocketLocation(FName("S_Muzzle"))).Rotation();
			DrawDebugLine(GetWorld(), Start, Hit.Location, FColor::Blue, false, 2.f, 0, 2.f);
		}
		bullet = GetWorld()->SpawnActor<ABullet>(BulletClass, Loc, Rot, BulletParams);
		AmmoLeft--;
	}
}

void AWeapon::Reload()
{	
	int32 NetAmmo = MagCapacity - AmmoLeft;
	if (MaxAmmo > NetAmmo)
	{
		AmmoLeft += NetAmmo;
		MaxAmmo -= NetAmmo;
	}
	else
	{
		AmmoLeft += MaxAmmo;
		MaxAmmo = 0;
	}
}

float AWeapon::GetFireRate()
{
	return FireRate;
}

void AWeapon::AddAmmo(int32 Ammo)
{
	MaxAmmo += Ammo;
}

UStaticMeshComponent* AWeapon::GetCurrentOptic()
{
	return CurrentOptic;
}

void AWeapon::AttachOptic()
{
	CurrentOptic->AttachToComponent(SKMesh, FAttachmentTransformRules::KeepRelativeTransform, FName("S_Sight"));
}