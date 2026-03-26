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
