// Fill out your copyright notice in the Description page of Project Settings.


#include "GHCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "GHAttributeSet.h" 

// Sets default values
AGHCharacterBase::AGHCharacterBase()
{
	//GAS Setup
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);
	AttributeSet = CreateDefaultSubobject<UGHAttributeSet>(TEXT("AttributeSet"));

}

// Called when the game starts or when spawned
void AGHCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	BindAttributeDelegates();
}

void AGHCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void AGHCharacterBase::HandleHealthUpdated(float CurrentHealth)
{
}

UAbilitySystemComponent* AGHCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AGHCharacterBase::InitializeAbilitySystem()
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void AGHCharacterBase::BindAttributeDelegates()
{
	if (!AttributeSet)
	{
		return;
	}

	AttributeSet->OnHealthUpdatedDelegate.AddUObject(this, &AGHCharacterBase::HandleHealthUpdated);
}
