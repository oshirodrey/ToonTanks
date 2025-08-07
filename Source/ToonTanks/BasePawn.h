// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn(); // Constructor declaration


private:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, meta= (AllowPrivateAccess = "true"),Category = "Components")
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, meta= (AllowPrivateAccess = "true"),Category = "Components")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, meta= (AllowPrivateAccess = "true"),Category = "Components")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, meta= (AllowPrivateAccess = "true"),Category = "Components")
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly ,BlueprintReadWrite, meta= (AllowPrivateAccess = "true"),Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass; // Class of the projectile to spawn

	UPROPERTY(EditAnywhere, Category = "Combat")
	float MaxHealth = 100.f; // Maximum health of the pawn
	


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float GetMaxHealth() const { return MaxHealth; } // Getter for maximum health

protected:
	void RotateTurret(FVector LookAtTarget);
	void Fire(); // Function to handle firing logic
	UStaticMeshComponent* GetTurretMesh() const { return TurretMesh; } // Getter for turret mesh
};
