// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "DrawDebugHelpers.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!AimingComponent) { return; }
		FoundAimingComponent(AimingComponent);

	isPlayerDead = false;

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
	//UE_LOG(LogTemp, Warning, TEXT("Player controller ticking!"));
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn) 
	{
		auto PlayerTank = Cast<ATank>(InPawn);
		if (!ensure(PlayerTank)) { return; }

		PlayerTank->onDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);

	}
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!AimingComponent) { return; }

	FVector HitLocation; //Out parameter
	if (GetSightRayHitLocation(HitLocation)) 
	{

		AimingComponent->AimAt(HitLocation);


	}

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);

	auto ScreenLocation = FVector2D(ViewPortSizeX * CrossHairXLocation, ViewPortSizeY * CrossHairYLocation);
	//UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString());


	FVector OutLookDirection;
	
	if (GetLookDirection(ScreenLocation, OutLookDirection))
	{
		//UE_LOG(LogTemp, Warning, TEXT("World Direction: %s"), *OutLookDirection.ToString());
		return GetLookVectorHitLocation(OutLookDirection, OutHitLocation);
	}


	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const
{
	FVector OutWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, OutWorldLocation, OutLookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor(255, 0, 0), false, 5.f, ECC_WorldStatic, 1.f);

	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Camera)
		) 
	{
		OutHitLocation = HitResult.Location;
		return true;
	}

	OutHitLocation = FVector(0);
	return false;
}

void ATankPlayerController::OnPossessedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("PLAYER TANK RECIEVED!"))

	StartSpectatingOnly();

	isPlayerDead = true;
}

bool ATankPlayerController::callDeathScreen(bool dead)
{
	return isPlayerDead;
}
