// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"


void ATurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    //Find the dist to the tank
    FVector TankLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
    float DistanceToTank = FVector::Distance(TankLocation, GetActorLocation());

    // If the tank is within range, rotate towards it
    if (DistanceToTank <= FireRange)
    {
        RotateTurret(TankLocation);
        // Optionally, you can implement firing logic here
        if (GetWorld()->GetTimeSeconds() - LastFireTime >= FireRate)
        {
            LastFireTime = GetWorld()->GetTimeSeconds(); // Update the last fire time
            Fire();
        }

    }
    else
    {   ///If the tank is out of range rotate the turret around its own axis 
        FRotator NewRotation = FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f);
        GetTurretMesh()->AddLocalRotation(NewRotation, true);
    }

    // If the tank is within firing range, fire at it

    // Implement turret-specific logic here, such as tracking targets or firing
}

