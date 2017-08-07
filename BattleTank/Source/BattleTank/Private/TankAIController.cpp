// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"
#include "Tank.h"		// so we can implement OnDeath()


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn *InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// subscribe to tank death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
 }

void ATankAIController::OnTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Death broadcast received!"));
	GetPawn()->DetachFromControllerPendingDestroy();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Get Player location

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }	// TODO ensure fires on Tank Death
	
	// TODO Move to player
	MoveToActor(PlayerTank, AcceptanceRadius);

	// Aim towards player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	// Fire when ready
	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();		// TODO Limit firing rate
	}
}

