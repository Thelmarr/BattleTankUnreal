// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "Turret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel *BarrelToSet, UTurret *TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector WorldSpaceAim, float Speed)
{
	if (!Barrel) { return; }

	FVector OutVelocity = FVector(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("ProjectileStart"));

	if (UGameplayStatics::SuggestProjectileVelocity(
													this, 
													OutVelocity, 
													StartLocation, 
													WorldSpaceAim, 
													Speed,
													0,
													0,
													0,
													ESuggestProjVelocityTraceOption::DoNotTrace ))
	{

		auto AimDirection = OutVelocity.GetSafeNormal();

		MoveBarrel(AimDirection);
		MoveTurret(AimDirection);

			// Get socket location
			// Rotate (azimuth and height)
			
		return;
	}
	else 
	{ 
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: No aiming solution found!"), Time);
		return;
	}
}

void UTankAimingComponent::MoveBarrel(FVector PitchAngle)
{
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = PitchAngle.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;

	Barrel->Elevate(DeltaRotator.Pitch);
	// TODO Move in desired direction at fixed speed per time (!)
}

void UTankAimingComponent::MoveTurret(FVector YawAngle)
{
	if (!Barrel || !Turret) return;
	auto TurretRotation = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = YawAngle.Rotation();
	auto DeltaRotator = AimAsRotator - TurretRotation;

	Turret->Rotate(DeltaRotator.Yaw);
}