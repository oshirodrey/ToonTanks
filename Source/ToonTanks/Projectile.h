// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, meta= (AllowPrivateAccess = "true"),Category = "Components")
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float Speed = 2000.f; // Speed of the projectile
	
	FTimerHandle FlyTimerHandle; // Timer handle for projectile movement

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
