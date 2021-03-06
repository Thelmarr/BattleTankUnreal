// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming colors

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	NoAmmo
};


class UTankBarrel;
class UTurret;
class AProjectile;

// Holds barrel's properties

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void BeginPlay() override;

	void AimAt(FVector WorldSpaceAim);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel *BarrelToSet, UTurret *TurretToSet);

	UFUNCTION(BlueprintCallable)
	void Fire();

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	// TODO remove once firing is moved
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 10000.f;	// equals 100 m/s

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float TimeToReloadinSeconds = 3;

	double LastFireTime = 0;

	bool IsBarrelMoving();

	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable)
	int32 GetAmmo() const;
private:
	UTankBarrel *Barrel = nullptr;
	UTurret *Turret = nullptr;
	void MoveBarrel(FVector PitchAngle);
	void MoveTurret(FVector YawAngle);

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	FVector AimingVector;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float AimTolerance = 0.075;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 AmmoShells = 3;
protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;
};
