// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveComponent.h"

// Sets default values for this component's properties
UMoveComponent::UMoveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UMoveComponent::AddPlayerMovement(FVector Direction, float Value)
{
	Direction = Direction * Value;
	GetOwner()->AddActorWorldOffset(Direction);
}

void UMoveComponent::AddPlayerRotation(FQuat Rotation)
{
	//MeshComp->AddLocalRotation(Rotation);
	GetOwner()->AddActorWorldRotation(Rotation);
}
