// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_SpellProjectile.generated.h"

class AGHSpellProjectile;

UCLASS()
class GHCOMBATPROTOTYPE_API UGA_SpellProjectile : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_SpellProjectile();

protected:
	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell")
	TSubclassOf<AGHSpellProjectile> ProjectileClass;

	/** Forward spawn offset from avatar */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell")
	float SpawnForwardOffset = 100.f;

	/** Upward spawn offset if needed */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell")
	float SpawnUpOffset = 50.f;

public:
	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData
	) override;
};
