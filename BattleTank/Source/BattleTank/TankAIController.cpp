// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "TankAimingComponent.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("AI controller tick working!"));

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();


	if (!PlayerTank && !ControlledTank) { return; }

		MoveToActor(PlayerTank, AcceptanceRadius);

		auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		if (AimingComponent->GetFiringState() == EFiringState::Locked)
		{
			AimingComponent->Fire();
		}
	
}
