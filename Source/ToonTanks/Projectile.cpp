// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent = ProjectileMesh;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Fly(DeltaTime); // Call the Fly function to handle projectile movement

}

void AProjectile::Fly(float DeltaTime)
{
	// Move forward in the direction the projectile is facing
	FVector DeltaLocation = FVector::ZeroVector; // Initialize DeltaLocation
	// Implement the logic for projectile movement here.
	DeltaLocation = GetActorForwardVector() * Speed * DeltaTime; // Calculate the movement delta based on speed and delta time
	AddActorLocalOffset(DeltaLocation, true); // Move the projectile forward
	// This could involve updating the position based on velocity, applying gravity, etc.
}