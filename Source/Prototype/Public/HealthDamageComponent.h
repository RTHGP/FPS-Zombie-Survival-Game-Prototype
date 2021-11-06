// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthDamageComponent.generated.h"

class AMyGameMode;
class AEnemy;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROTOTYPE_API UHealthDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthDamageComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float Health;
	
	void Damage(float DamageAmount);

private:
	
	bool bIsDamaged;

	float HealthRegenTimer;

	float RegenHealthDelay;

	AMyGameMode* Gm;

	AEnemy* IsEnemy;

	bool bEnemyOwner = false;

};
