// Fill out your copyright notice in the Description page of Project Settings.


#include "GHAttributeSet.h"
#include "Net/UnrealNetwork.h"

UGHAttributeSet::UGHAttributeSet()
{
	InitHealth(100.f);
	InitMaxHealth(100.f);
}

void UGHAttributeSet::OnHealthUpdated(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGHAttributeSet, Health, OldValue);
}

void UGHAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UGHAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
}

void UGHAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if(Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		float newHealth = GetHealth();
		newHealth = FMath::Clamp(newHealth, 0.f, GetMaxHealth());
		SetHealth(newHealth);
	}
}

void UGHAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UGHAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGHAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
}
