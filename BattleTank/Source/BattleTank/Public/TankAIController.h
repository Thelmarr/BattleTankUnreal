// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ATank *GetControlledTank();

	void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	const ATank *GetPlayerTank();
};
