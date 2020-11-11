// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrackNew.h"

UTankTrackNew::UTankTrackNew()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrackNew::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UE_LOG(LogTemp, Warning, TEXT("Track Ticking"))

}


void UTankTrackNew::SetThrottle(float Throttle)
{
	//auto Name = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s Throttle: %f"), *Name, Throttle);

	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}