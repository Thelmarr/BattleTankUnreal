// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController not possessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController possessing: %s"), *(ControlledTank->GetName()));
	}

	auto PlayerTank = GetPlayerTank();

	UE_LOG(LogTemp, Warning, TEXT("AIController targeting at: %s"), *(PlayerTank->GetName()));
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Get Player location

	if (GetPlayerTank())
	{
		// TODO Move to player

		// Aim towards player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		// Fire when ready
	}
}

const ATank * ATankAIController::GetPlayerTank()
{
	APawn *Target = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!Target)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController cannot find player tank"));
		return nullptr;
	}
	else
	{
		
		return Cast<ATank>(Target);
	}
};

 ATank *ATankAIController::GetControlledTank()
{
	return Cast<ATank>(GetPawn());
};