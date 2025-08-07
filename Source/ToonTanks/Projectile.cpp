// Fill out your copyright notice in the Description page of Project Settings.

#include "TimerManager.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = Speed;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(FlyTimerHandle, this, &AProjectile::Fly, 0.01f, true); // Set a timer to call Fly every 0.01 seconds
	
}


void AProjectile::Fly()
{

//	AddActorLocalOffset(GetActorForwardVector() * Speed, true); // Move the projectile forward
	// This could involve updating the position based on velocity, applying gravity, etc.
}