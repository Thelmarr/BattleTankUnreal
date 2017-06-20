// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel *BarrelToSet)
{
	Barrel = BarrelToSet;
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
													ESuggestProjVelocityTraceOption::DoNotTrace ))
	{

		auto AimDirection = OutVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s aiming at: %s"),*TankName ,*AimDirection.ToString());

		MoveBarrel(AimDirection);

			// Get socket location
			// Rotate (azimuth and height)
			
		return;
	}
	else { return; }
}

void UTankAimingComponent::MoveBarrel(FVector Angle)
{
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = Angle.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;

	Barrel->Elevate(5);

	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *AimAsRotator.ToString());
	// TODO Move in desired direction at fixed speed per time (!)
}