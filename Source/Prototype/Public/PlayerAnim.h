// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnim.generated.h"

class ASPlayer;
class AWeapon;

/**
 * 
 */
UCLASS()
class PROTOTYPE_API UPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	
	void NativeBeginPlay() override;

	void NativeUpdateAnimation(float DeltaTime) override;

public:
	
	UPROPERTY(BlueprintReadOnly)
	FTransform RelativeHandTransform;
	
	UPROPERTY(BlueprintReadOnly)
	FTransform RelativeSightTransform;

	UPROPERTY(BlueprintReadOnly)
	float Alpha;

	int IsADS;

	bool IsInterp;
	
	void InterpAlpha();

private:

	FTimerHandle Delay, Delay1, cw;

	ASPlayer* PlayerCharacter;
	
	AWeapon* Weapon;

	void CastWeapon();
	
	void GetRelativeHandTransform();

	void GetRelativeSightTransform();

};
