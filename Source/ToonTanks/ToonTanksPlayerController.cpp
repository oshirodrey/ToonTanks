// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/Pawn.h"
#include "ToonTanksPlayerController.h"

void AToonTanksPlayerController::SetPlayerEnableState(bool bPlayerEnabled)
{
    bPlayerEnabled ? GetPawn()->EnableInput(this) : GetPawn()->DisableInput(this);
    bShowMouseCursor = bPlayerEnabled; // Show or hide the mouse cursor based on player state
}