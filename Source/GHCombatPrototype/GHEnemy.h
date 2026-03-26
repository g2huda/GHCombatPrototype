// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GHCharacterBase.h"
#include "GHEnemy.generated.h"

class AGHCharacterBase;
/**
 *  A simple player-controllable third person character that has an Ability System Component and a health 
 *  Attribute Set.
 *  Implements a controllable orbiting camera
 */
UCLASS(abstract)
class AGHEnemy : public AGHCharacterBase
{
	GENERATED_BODY()

public:

	/** Constructor */
	AGHEnemy();

protected:

	virtual void BeginPlay() override;
};
