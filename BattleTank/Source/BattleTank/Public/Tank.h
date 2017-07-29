// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimingComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

public:		
	UFUNCTION(BlueprintCallable)
	void Fire();

private:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;
	
	// TODO remove once firing is moved
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 100000.f;	// equals 1000 m/s

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float TimeToReloadinSeconds = 3;

	double LastFireTime = 0;

	UTankBarrel *Barrel;
	UTurret *Turret;
};
