// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	//ATank* PlayerTank = GetPlayerTank();
	//if (!PlayerTank)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("AIController Not finding player tank."));
	//} 
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("AIController found player tank: %s"), *PlayerTank->GetName());
	//}

	// UE_LOG(LogTemp, Warning, TEXT("PlayerController : %s."), *PlayerTank->GetName());
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

		//TODO fix firing
		// ControlledTank->Fire();
	
}
