// Copyright Epic Games, Inc. All Rights Reserved.

#include "GA_SpellProjectile.h"

#include "GHSpellProjectile.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "AbilitySystemComponent.h"
#include "Engine/World.h"
#include "GHCombatPrototype.h"

UGA_SpellProjectile::UGA_SpellProjectile()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_SpellProjectile::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	UE_LOG(LogGHCombatPrototype, Log, TEXT("UGA_SpellProjectile::ActivateAbility called"));

	if (!ActorInfo || !ActorInfo->AvatarActor.IsValid())
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	AActor* AvatarActor = ActorInfo->AvatarActor.Get();
	if (!AvatarActor || !ProjectileClass)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	// Server-authoritative spawn only
	if (!AvatarActor->HasAuthority())
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}

	const FVector ForwardVector = AvatarActor->GetActorForwardVector();
	const FVector SpawnLocation =
		AvatarActor->GetActorLocation() +
		ForwardVector * SpawnForwardOffset +
		FVector(0.f, 0.f, SpawnUpOffset);

	const FRotator SpawnRotation = ForwardVector.Rotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = AvatarActor;
	SpawnParams.Instigator = Cast<APawn>(AvatarActor);
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AGHSpellProjectile* Projectile = AvatarActor->GetWorld()->SpawnActor<AGHSpellProjectile>(
		ProjectileClass,
		SpawnLocation,
		SpawnRotation,
		SpawnParams
	);

	if (Projectile)
	{
		Projectile->InitializeProjectile(AvatarActor);
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}
