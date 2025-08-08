// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Turret.h"
#include "ToonTanksPlayerController.h"
#include "ToonTanksGameMode.h"


void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();
    HandleGameStart(); // Handle game start logic here
    
   
}

void AToonTanksGameMode::HandleGameStart()
{
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    ToonTanksPlayerController->SetPlayerEnableState(false); // Disable player input initially
    FTimerHandle PlayerEnableTimerHandle;
 // The TimerDelegate will (1) call the Object in a class create by user,(2) the function it will call and (3) the value it will pass un
    FTimerDelegate PLayerEnableTimerDelegate= FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnableState, true );
    GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PLayerEnableTimerDelegate, StartDelay,false);
}

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
    // Handle the actor's death logic here
    if (DeadActor == Tank)
    {
        if (ToonTanksPlayerController)
        {
            ToonTanksPlayerController->SetPlayerEnableState(false); // Disable player input
        }
       
    }
    else if (ATurret * DeadTurretActor = Cast<ATurret>(DeadActor))
    {
        DeadTurretActor->HandleDestruction(); // Call the turret's destruction handler
    }
    
}
