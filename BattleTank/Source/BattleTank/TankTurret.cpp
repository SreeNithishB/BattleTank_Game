// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	//auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f: Barrel Elevate called at speed %f"), Time, RelativeSpeed);

	RelativeSpeed = FMath::Clamp<int>(RelativeSpeed, -1, 1);

	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = GetRelativeRotation().Yaw + RotationChange;


	SetRelativeRotation(FRotator(0, RawNewRotation, 0));

	//UE_LOG(LogTemp, Warning, TEXT("Turret Rotate is being called"));
}