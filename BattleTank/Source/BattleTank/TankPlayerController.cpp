// Fill out your copyright notice in the Description page of Project Settings.
#include "Public/Tank.h"
#include "BattleTank.h"
#include "TankPlayerController.h"

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
