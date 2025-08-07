// Fill out your copyright notice in the Description page of Project Settings.

#include "TimerManager.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
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
	ProjectileMovement->MaxSpeed = Speed;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	auto MyOwner = GetOwner();
	if (MyOwner == nullptr || OtherActor == nullptr || OtherActor == MyOwner) return;

	auto MyOwnerInstigator = MyOwner->GetInstigatorController();
	auto DamageType = UDamageType::StaticClass();
	// Handle what happens when the projectile hits something
	if (OtherActor && OtherActor != MyOwner && OtherActor != this)
	{
		
		UGameplayStatics::ApplyDamage(OtherActor, 20.f, nullptr, this, nullptr); 
	}
	Destroy(); // Destroy the projectile after hitting

}
