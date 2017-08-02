// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"
#include "Tank.h"

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtCrosshair();
}


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
};

void ATankPlayerController::AimAtCrosshair()
{
	if (!GetPawn()) { return; } // e.g. if not possessing
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation;	// OUT Parameter

	if (GetSightRayHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
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

void ATankPlayerController::SetPawn(APawn *InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// subscribe to tank death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPlayerTankDeath);
	}
}

void ATankPlayerController::OnPlayerTankDeath()
{
	StartSpectatingOnly();
}