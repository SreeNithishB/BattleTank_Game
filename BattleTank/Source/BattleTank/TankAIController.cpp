// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

ATank* ATankAIController::GetControlledTank() const 
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay() 
{
	ATank* ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController Not Possesing a tank."));
	} 
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController Possesing: %s"), *ControlledTank->GetName());
	}
}