// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATurret : public ABasePawn
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireRange = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float RotationSpeed = 112.0f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireRate = 2.5f;

	float LastFireTime = 0.0f; // To track the last time the turret fired


//	FTimerHandle FireRateTimerHandle;

	//void CheckFireCondition();

protected:
	// Called when the game starts or when spawned
	virtual void Tick(float DeltaTime) override;
	
};
