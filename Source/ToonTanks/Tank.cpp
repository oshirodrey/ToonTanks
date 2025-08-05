// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"

ATank::ATank()
{
    // Initialize the SpringArm component
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
   
    // Initialize the Camera component
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm); // Attach the camera to the spring arm

    Forward1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Forward1"));
    Forward1->SetupAttachment(RootComponent);
    Forward1->SetRelativeLocation(FVector(0.f, 0.f, -75.898837));
    Forward1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    Forward1->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    Forward2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Forward2"));
    Forward2->SetupAttachment(RootComponent);
    Forward2->SetRelativeLocation(FVector(0.f, 0.f, -75.898837));
    Forward2->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    Forward2->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    Forward3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Forward3"));
    Forward3->SetupAttachment(RootComponent);
    Forward3->SetRelativeLocation(FVector(0.f, 0.f, -75.898837));
    Forward3->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    Forward3->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    //#################################################//
    Back1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Back1"));
    Back1->SetupAttachment(RootComponent);
    Back1->SetRelativeLocation(FVector(0.f, 0.f, -75.898837));
    Back1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    Back1->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

    Back2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Back2"));
    Back2->SetupAttachment(RootComponent);
    Back2->SetRelativeLocation(FVector(0.f, 0.f, -75.898837));
    Back2->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    Back2->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

    Back3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Back3"));
    Back3->SetupAttachment(RootComponent);
    Back3->SetRelativeLocation(FVector(0.f, 0.f, -75.898837));
    Back3->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    Back3->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    //#################################################//
    TurnLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurnLeft"));
    TurnLeft->SetupAttachment(RootComponent);
    TurnLeft->SetRelativeLocation(FVector(0.f, 0.f, -75.898837));
    TurnLeft->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    TurnLeft->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    TurnRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurnRight"));
    TurnRight->SetupAttachment(RootComponent);
    TurnRight->SetRelativeLocation(FVector(0.f, 0.f, -75.898837));
    TurnRight->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    //Add the components to the array for easy access
    TankMeshComponents.Add(Forward1);
    TankMeshComponents.Add(Forward2);
    TankMeshComponents.Add(Forward3);  
    TankMeshComponents.Add(Back1);
    TankMeshComponents.Add(Back2);
    TankMeshComponents.Add(Back3);
    TankMeshComponents.Add(TurnLeft);
    TankMeshComponents.Add(TurnRight);
    
}

// Called to bind functionality to input 
//(this function will be called every frame, just like Tick)
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    CurrentMoveInput = 0.f;
    CurrentTurnInput = 0.f;
    for (UStaticMeshComponent* MeshComponent : TankMeshComponents)
    {
        if (MeshComponent->IsVisible())
        {
            MeshComponent->SetVisibility(false);  // Show the mesh

        }
    }
    // Bind input actions and axes here
    PlayerInputComponent->BindAxis("MoveForward", this, &ATank::Move);
    // You can bind other inputs like turning or firing here as well
    PlayerInputComponent->BindAxis("Turn", this, &ATank::Turn);

    
    

}
// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
    PlayerControllerRef = Cast<APlayerController>(GetController());
    
	
}


void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Call the function to set the visibility of the tank arrows
    SetTankArrowsVisibility();
    //Create a red sphere at the cursor's location 
    if (PlayerControllerRef)
    {
        FVector HitLocation;
        FHitResult HitResult;
        PlayerControllerRef->GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility, 
            false, 
            HitResult);
        HitLocation = HitResult.ImpactPoint;

        // Draw a debug sphere at the hit location
        DrawDebugSphere(GetWorld(), HitLocation, 50.f, 12, FColor::Red, false, -1.f);
        RotateTurret(HitLocation); // Rotate the turret towards the hit location
    }

    
}

void ATank::Move(float Value)
{   
    CurrentMoveInput = Value; // Store the current move input value
    FVector DeltaLocation = FVector::ZeroVector;
    //DeltaLocation.X = Value * MovementSpeed * GetWorld()->GetDeltaSeconds(); // Move forward/backward based on input
    DeltaLocation.X = Value * MovementSpeed * UGameplayStatics::GetWorldDeltaSeconds(this); // 2 way of getting delta seconds
    AddActorLocalOffset(DeltaLocation, true); // Move forward/backward based on input

    
}

void ATank::Turn(float Value)
{   
    CurrentTurnInput = Value; // Store the current turn input value
    FRotator NewRotation = FRotator(0.0f, 0.0f, 0.0f); // Create a new rotation based on the input

    //Just to make sure the tank turns in the right direction
    if(CurrentMoveInput <0 )
    {
        NewRotation.Yaw =   -( Value * TurnRate * GetWorld()->GetDeltaSeconds()); // Turn left/right based on input  


    }
    else
    {    
        NewRotation.Yaw =   ( Value * TurnRate * GetWorld()->GetDeltaSeconds());
    }
    AddActorLocalRotation(NewRotation, true); // Apply rotation to the tank 

}
void ATank::SetTankArrowsVisibility()
{
    for (UStaticMeshComponent* MeshComponent : TankMeshComponents)
    {
        if (MeshComponent->IsVisible())
        {
            MeshComponent->SetVisibility(false);  // Show the mesh

        }
    }

    // Example: Toggle Forward1 visibility based on input value every frame
    if (CurrentMoveInput > 0 && CurrentTurnInput > 0)
    {
        Forward3->SetVisibility(true);

    }
    else if (CurrentMoveInput > 0 && CurrentTurnInput < 0)
    {
        Forward2->SetVisibility(true);
    }
     else if (CurrentMoveInput > 0 && CurrentTurnInput == 0)
    {
        Forward1->SetVisibility(true);
    }
    else if (CurrentMoveInput < 0 && CurrentTurnInput > 0)
    {
        Back2->SetVisibility(true);
    }
    else if (CurrentMoveInput < 0 && CurrentTurnInput < 0)
    {
        Back3->SetVisibility(true);
    }
    else if (CurrentMoveInput < 0 && CurrentTurnInput == 0)
    {
        Back1->SetVisibility(true);
    }
    else if (CurrentTurnInput < 0)
    {
        TurnLeft->SetVisibility(true);
    }
    else if (CurrentTurnInput > 0)
    {
        TurnRight->SetVisibility(true);
    }


    // You can add more per-frame logic here
    CurrentMoveInput = 0.f;
    CurrentTurnInput = 0.f;
}
