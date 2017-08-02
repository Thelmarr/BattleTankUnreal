// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Turret.h"


void UTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	auto Time = GetWorld()->GetTimeSeconds();

	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;
	auto Rotation = FMath::Clamp<float>(RawNewRotation, MinDegreesRotation, MaxDegreesRotation);

	SetRelativeRotation(FRotator(0, Rotation, 0));
}


