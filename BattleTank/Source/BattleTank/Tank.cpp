// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


float ATank::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;

	if (CurrentHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Died."))
	}

    return DamageToApply;
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}






