// Copyright Epic Games, Inc. All Rights Reserved.

#include "GHEnemy.h"
#include "Components/CapsuleComponent.h"

AGHEnemy::AGHEnemy()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
}

void AGHEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitializeAbilitySystem();
}

void AGHEnemy::HandleHealthUpdated(float CurrentHealth)
{
	if(CurrentHealth <= 0.f)
	{
		// Handle death (e.g., play animation, disable collision, etc.)
		UE_LOG(LogTemp, Warning, TEXT("%s has died."), *GetName());
		if (HasAuthority())
		{
			//ragdoll, play death animation, etc. could be implemented here
			Destroy();
		}
	}
}
