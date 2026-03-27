// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GHCharacterBase.generated.h"

class UAbilitySystemComponent;
class UGHAttributeSet;
class UGameplayAbility;
class UInputAction;

UCLASS()
class GHCOMBATPROTOTYPE_API AGHCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGHCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;


protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION()
	virtual void HandleHealthUpdated(float CurrentHealth);

	/** GAS Core */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivate))
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UGHAttributeSet> AttributeSet;


	/** internal init */
	void InitializeAbilitySystem();
	void BindAttributeDelegates();

public:

	/** Returns AttributeSet subobject **/
	FORCEINLINE UGHAttributeSet* GetAttributeSet() const { return AttributeSet; }
};
