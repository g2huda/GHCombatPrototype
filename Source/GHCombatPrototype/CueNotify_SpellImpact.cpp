// Copyright Epic Games, Inc. All Rights Reserved.

#include "CueNotify_SpellImpact.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"

UCueNotify_SpellImpact::UCueNotify_SpellImpact()
{
	GameplayCueTag = FGameplayTag::RequestGameplayTag(FName("GameplayCue.Spell.Impact"));//todo: add to config ini
}

bool UCueNotify_SpellImpact::HandlesEvent(EGameplayCueEvent::Type EventType) const
{
	return EventType == EGameplayCueEvent::Executed;
}

void UCueNotify_SpellImpact::HandleGameplayCue(
	AActor* MyTarget,
	EGameplayCueEvent::Type EventType,
	const FGameplayCueParameters& Parameters) 
{
	Super::HandleGameplayCue(MyTarget, EventType, Parameters);

	if (EventType != EGameplayCueEvent::Executed)
	{
		return;
	}

	FVector SpawnLocation = Parameters.Location;
	FRotator SpawnRotation = FRotator::ZeroRotator;

	if (SpawnLocation.IsNearlyZero() && MyTarget)
	{
		SpawnLocation = MyTarget->GetActorLocation();
	}

	if (ImpactParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			MyTarget ? MyTarget->GetWorld() : nullptr,
			ImpactParticle,
			SpawnLocation,
			SpawnRotation,
			true
		);
	}

	if (ImpactSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			MyTarget ? MyTarget->GetWorld() : nullptr,
			ImpactSound,
			SpawnLocation
		);
	}
}
