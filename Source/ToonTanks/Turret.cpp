// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Tank.h"
#include "Turret.h"

void ATurret::BeginPlay()
{
    Super::BeginPlay();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    if (Tank)
    {
        // Start a timer to check the fire condition periodically
        GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &ATurret::CheckFireCondition, FireRate, true);
    }
}
void ATurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    //Find the dist to the tank
    FVector TankLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
    float DistanceToTank = FVector::Distance(TankLocation, GetActorLocation());

    // If the tank is within range, rotate towards it
    if (InFireRange())
    {
        RotateTurret(TankLocation);
     
    }
    else
    {   ///If the tank is out of range rotate the turret around its own axis 
        FRotator NewRotation = FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f);
        GetTurretMesh()->AddLocalRotation(NewRotation, true);
    }

    
    // If the tank is within firing range, fire at it

    // Implement turret-specific logic here, such as tracking targets or firing
}
void ATurret::CheckFireCondition()
{ 
    if (Tank)
    {   
        float DistanceToTank = FVector::Distance(Tank->GetActorLocation(), GetActorLocation());
        if (InFireRange())
        {
            Fire(); // Call the Fire function if the tank is within range
        }
        
    }
}

bool ATurret::InFireRange()
{
    if (Tank)
    { 
        float DistanceToTank = FVector::Distance(Tank->GetActorLocation(), GetActorLocation());
        return DistanceToTank <= FireRange;
    }
    return false; // If no tank is found, return false
}

void ATurret::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy(); // Call the base class destruction
}