// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "HealthDamageComponent.h"
#include "DrawDebugHelpers.h"
#include "SPlayer.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SComp = CreateDefaultSubobject<USphereComponent>(TEXT("CapsuleComp"));
	RootComponent = SComp;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(SComp);
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetupAttachment(SComp);
	SphereComp->SetSphereRadius(2000.f);
	HDComp = CreateDefaultSubobject<UHealthDamageComponent>(TEXT("HDComp"));


}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	HDComp->Health = Health;
	bIsNearPlayer = false;
	bIsStuck = false;
	bFoundPlayer = false;
	SComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::BeginOverlap);
	SComp->OnComponentEndOverlap.AddDynamic(this, &AEnemy::EndOverlap);

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::BeginOverlap2);
	SphereComp->OnComponentEndOverlap.AddDynamic(this, &AEnemy::EndOverlap2);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemy::DamageSelf(float DamageAmount)
{
	HDComp->Damage(DamageAmount);
}

float AEnemy::GetMoveSpeed()
{
	return MoveSpeed;
}

float AEnemy::GetStopingDistance()
{
	return StopingDistance;
}

float AEnemy::GetPlayerDamageAmount()
{
	return PlayerDamageAmount;
}

void AEnemy::MakeJump()
{
	MeshComp->AddImpulse(FVector(0, 0, JumpSpeed));
}

void AEnemy::DropAmmo()
{	
	int rn = FMath::RandRange(0, 3);
	if (rn == 2)
	{
		UClass* AD = AmmoDrop;
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		GetWorld()->SpawnActor<AActor>(AD, GetActorLocation(), FRotator(0), SpawnParams);
	}
}

void AEnemy::BeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//bIsStuck = true;
	UE_LOG(LogTemp, Warning, TEXT("%s"), *OtherActor->GetName());
	/*auto MainPlayer = Cast<ASPlayer>(OtherActor);
	if (MainPlayer)
	{
		bIsNearPlayer = true;
		UE_LOG(LogTemp, Warning, TEXT("%s"), *MainPlayer->GetName());
	}
	else
	{
		bIsStuck = true;
	}*/
}

void AEnemy::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//bIsStuck = false;
	/*if (bIsNearPlayer)
		bIsNearPlayer = false;*/
}

void AEnemy::BeginOverlap2(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto MainPlayer = Cast<ASPlayer>(OtherActor);
	if (MainPlayer)
	{
		bFoundPlayer = true;
	}
}

void AEnemy::EndOverlap2(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{	
	if (FollowPlayerTime >= 5.f)
	{
		bFoundPlayer = false;
		FollowPlayerTime = 0.f;
	}
}
