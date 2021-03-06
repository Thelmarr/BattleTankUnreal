// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay(); // Needed for BP Begin Play to run!

	CurrentHealth = StartingHealth;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController *EventInstigator, AActor *DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 AppliedDamage = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= AppliedDamage;

	UE_LOG(LogTemp, Warning, TEXT("Damage amount: %f, Applied damage: %i"), DamageAmount, AppliedDamage);

	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}

	return AppliedDamage;
}

float ATank::GetHealthPercent() const
{
	return ((float)CurrentHealth / (float)StartingHealth);
}