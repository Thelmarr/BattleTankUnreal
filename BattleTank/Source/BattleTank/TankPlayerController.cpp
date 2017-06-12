// Fill out your copyright notice in the Description page of Project Settings.
#include "Tank.h"
#include "BattleTank.h"
#include "TankPlayerController.h"



const ATank *ATankPlayerController::GetControlledTank() 
{
	return Cast<ATank>(GetPawn());
};
