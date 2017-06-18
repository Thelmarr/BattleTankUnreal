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

	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	float CrosshairPixelX = ViewportSizeX*CrosshairXLocation;
	float CrosshairPixelY = ViewportSizeY*CrosshairYLocation;

	auto ScreenLocation= FVector2D(CrosshairPixelX, CrosshairPixelY);

	FVector Lookdirection;

	if (GetLookdirection(ScreenLocation, Lookdirection))
	{
		GetLookVectorHitLocation(Lookdirection, location);
	}
	// Raycast to crosshair
	// if(Raycast hit something)
	// return location OUT
	// return true

	// else
	//location = FVector(1.0);
	return true;
}

const bool ATankPlayerController::GetLookdirection(FVector2D ScreenLocation, FVector &Direction)
{
	FVector projectlocation = { 0, 0, 0 };

	return DeprojectScreenPositionToWorld(ScreenLocation.X,
		ScreenLocation.Y,
		projectlocation,
		Direction); 
}

const bool ATankPlayerController::GetLookVectorHitLocation(FVector LookVector, FVector &TargetLocation)
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookVector*LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
	{
		TargetLocation = HitResult.Location;
		return true;
	}
	else
	{
		TargetLocation = { 0, 0, 0 };
		return false;
	}
}