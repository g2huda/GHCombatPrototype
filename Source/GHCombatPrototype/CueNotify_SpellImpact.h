// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "CueNotify_SpellImpact.generated.h"

class UParticleSystem;
class USoundBase;
class UMaterialInterface;

UCLASS()
class GHCOMBATPROTOTYPE_API UCueNotify_SpellImpact : public UGameplayCueNotify_Static
{
	GENERATED_BODY()

public:
	UCueNotify_SpellImpact();

	virtual bool HandlesEvent(EGameplayCueEvent::Type EventType) const override;

	virtual void HandleGameplayCue(
		AActor* MyTarget,
		EGameplayCueEvent::Type EventType,
		const FGameplayCueParameters& Parameters
	) override;

protected:
	/** particle system */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cue")
	TObjectPtr<UParticleSystem> ImpactParticle;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cue")
	TObjectPtr<USoundBase> ImpactSound;
};
