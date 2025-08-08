// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePawn.h"
#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	ABasePawn* BasePawn = Cast<ABasePawn>(GetOwner());
	if (BasePawn)
	{
		MaxHealth = BasePawn->GetMaxHealth();
	}
	else
	{
		MaxHealth = 100.f; // Fallback/default value
	}	
	CurrentHealth = MaxHealth; // Initialize current health to maximum health
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken); // Bind the damage event

	GameModeRef = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.f || CurrentHealth <= 0.f) return; // Ignore non-positive damage or if already dead

	CurrentHealth -= Damage; // Reduce current health by damage amount
	if (CurrentHealth <= 0.f)
	{
		// Handle death logic here, such as destroying the actor or triggering a death event
		if (GameModeRef)
		{
			GameModeRef->ActorDied(DamagedActor); // Notify the game mode that the actor has died
		}
	}
}
