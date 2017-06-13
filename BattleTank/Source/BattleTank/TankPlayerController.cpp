// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"
#include "Public/Tank.h"

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtCrosshair();
}


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *(ControlledTank->GetName()));
	}	
};

const ATank *ATankPlayerController::GetControlledTank() 
{
	return Cast<ATank>(GetPawn());
};

void ATankPlayerController::AimAtCrosshair()
{
	if (!GetControlledTank())	{return;}
	FVector HitLocation;	// OUT Parameter

	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit location: %s"), *HitLocation.ToString());

		// Get World Location through Crosshair
		// It it hits something
			// Tell controlled tank to aim at it
	}

}

const bool ATankPlayerController::GetSightRayHitLocation(FVector& location)
{
	FVector PlayerLocation;		// Get Player Location

	// Raycast to crosshair
	// if(Raycast hit something)
	// return location OUT
	// return true

	// else
	location = FVector(1.0);
	return true;
}