// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Tank Tracks are used for driving and applying other forces to the tank
 */
UCLASS( meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);


	// Max Force in Newton per Track 
	// current mass of Tank: 40000 kg; Acceleration: 5 m/s²
	UPROPERTY(EditDefaultsOnly)
	float MaxDrivingForce = 400000.f;
};
