// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthDamageComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "MyGameMode.h"
#include "Enemy.h"

// Sets default values for this component's properties
UHealthDamageComponent::UHealthDamageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthDamageComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	bIsDamaged = false;
	HealthRegenTimer = 0.f;
	IsEnemy = Cast<AEnemy>(GetOwner());
	if (IsValid(IsEnemy))
	{
		Gm = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		bEnemyOwner = true;
		//UE_LOG(LogTemp, Warning, TEXT("Begin play work!"));
	}
}


// Called every frame
void UHealthDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
	if (bIsDamaged)
	{	
		//UE_LOG(LogTemp, Warning, TEXT("work!"));
		RegenHealthDelay += DeltaTime;
		HealthRegenTimer += DeltaTime;
		if (HealthRegenTimer > 1.f && RegenHealthDelay >= 10.f)
		{
			Health += 1.f;
			HealthRegenTimer = 0.f;
		}
		if (Health >= 100.f)
			bIsDamaged = false;
	}
}


void UHealthDamageComponent::Damage(float DamageAmount)
{
	Health -= DamageAmount;
	if (!IsEnemy)
	{
		bIsDamaged = true;
		RegenHealthDelay = 0.f;
		HealthRegenTimer = 0.f;
	}
	UE_LOG(LogTemp, Warning, TEXT("%f"), Health);
	if (Health <= 0.f)
	{
		if (bEnemyOwner)
		{
			IsEnemy->DropAmmo();
			Gm->EnemyReduce();
		}
		GetOwner()->Destroy();
	}
}

