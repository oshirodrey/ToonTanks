// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
protected:
    float CurrentMoveInput = 0.f;
    float CurrentTurnInput = 0.f;
	TArray<UStaticMeshComponent*> TankMeshComponents;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:



	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, meta= (AllowPrivateAccess="true"), Category = "Components")
		class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta= (AllowPrivateAccess = "true"), Category = "Components")
		class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta= (AllowPrivateAccess = "true"), Category = "Tank Properties")
		float MovementSpeed = 1000.0f; // Speed of the tank movement	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta= (AllowPrivateAccess = "true"), Category = "Tank Properties")
		float TurnRate = 200.0f; // Speed of the tank turning

	//Plans (object) for the tank
		UPROPERTY(VisibleAnywhere,BlueprintReadWrite, meta= (AllowPrivateAccess="true"), Category = "Components")
		class UStaticMeshComponent* Forward1;
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta= (AllowPrivateAccess="true"), Category = "Components")
		class UStaticMeshComponent* Forward2;
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta= (AllowPrivateAccess="true"), Category = "Components")
		class UStaticMeshComponent* Forward3;
		//#################################################//
		UPROPERTY(VisibleAnywhere,BlueprintReadWrite, meta= (AllowPrivateAccess="true"), Category = "Components")
		class UStaticMeshComponent* Back1;
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta= (AllowPrivateAccess="true"), Category = "Components")
		class UStaticMeshComponent* Back2;
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta= (AllowPrivateAccess="true"), Category = "Components")
		class UStaticMeshComponent* Back3;
		//#################################################//
		UPROPERTY(VisibleAnywhere,BlueprintReadWrite, meta= (AllowPrivateAccess="true"), Category = "Components")
		class UStaticMeshComponent* TurnLeft;
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta= (AllowPrivateAccess="true"), Category = "Components")
		class UStaticMeshComponent* TurnRight;

	// Functions to handle movement and turning
	void Move(float Value);
	void Turn(float Value); 
	void SetTankArrowsVisibility();
	/////////
	APlayerController* PlayerController;

	

public:
	ATank(); // Decalration of the constructor
	
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction(); // Override to handle tank-specific destruction logic

	APlayerController* GetPlayerController() const { return PlayerController; } // Getter for player controller

	bool bStillAlive = true; // Flag to check if the tank is still alive
};
