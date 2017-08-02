// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent *AimCompRef);
public:

	void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void AimAtCrosshair();

	const bool GetSightRayHitLocation(FVector& location);
	const bool GetLookdirection(FVector2D ScreenLocation, FVector &Direction);
	const bool GetLookVectorHitLocation(FVector LookVector, FVector &TargetLocation);

	UFUNCTION()
	void OnPlayerTankDeath();

private:

	void SetPawn(APawn *InPawn);

	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairYLocation = 0.33333;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000;
};
