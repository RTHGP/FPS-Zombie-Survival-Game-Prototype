// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"
#include "TimerManager.h"
#include "SPlayer.h"
#include "Weapon.h"

void UPlayerAnim::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	PlayerCharacter = Cast<ASPlayer>(TryGetPawnOwner());

	if (PlayerCharacter)
	{	
		Alpha = 0.f;
		IsADS = 0.f;
		IsInterp = false;;
		GetWorld()->GetTimerManager().SetTimer(cw, this, &UPlayerAnim::CastWeapon, 0.1f, false);
		GetWorld()->GetTimerManager().SetTimer(Delay, this, &UPlayerAnim::GetRelativeSightTransform, 0.3f, false);
		GetWorld()->GetTimerManager().SetTimer(Delay1, this, &UPlayerAnim::GetRelativeHandTransform, 0.3f, false);
		
	}
}

void UPlayerAnim::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	if(IsInterp)
	InterpAlpha();
}

void UPlayerAnim::InterpAlpha()
{	
	if (IsADS == 1)
		Alpha = UKismetMathLibrary::FInterpTo(Alpha, IsADS, GetWorld()->GetDeltaSeconds(), 20.f);
	else
		Alpha = UKismetMathLibrary::FInterpTo(Alpha, IsADS, GetWorld()->GetDeltaSeconds(), 20.f);
	
	if (Alpha >= 1.f || Alpha <= 0.f)
		IsInterp = false;
}

void UPlayerAnim::CastWeapon()
{
	Weapon = Cast<AWeapon>(PlayerCharacter->GetPlayerWeapon());
}

void UPlayerAnim::GetRelativeHandTransform()
{
	FTransform OpticTransform = Weapon->CurrentOptic->GetSocketTransform(TEXT("S_Aim"));

	FTransform HandTransform = PlayerCharacter->GetPlayerMesh()->GetSocketTransform(TEXT("hand_r"));
	
	RelativeHandTransform = UKismetMathLibrary::MakeRelativeTransform(OpticTransform, HandTransform);
}

void UPlayerAnim::GetRelativeSightTransform()
{	
	FTransform CamTransform = PlayerCharacter->GetCameraComponent()->GetComponentTransform();
	
	FTransform HandTransform = PlayerCharacter->GetPlayerMesh()->GetComponentTransform();
	
	RelativeSightTransform = UKismetMathLibrary::MakeRelativeTransform(CamTransform, HandTransform);

	RelativeSightTransform.SetLocation(RelativeSightTransform.GetLocation() + RelativeSightTransform.GetRotation().GetForwardVector() * 30.f);
}
