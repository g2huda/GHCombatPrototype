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

void UGHAttributeSet::OnMaxHealthUpdated(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGHAttributeSet, MaxHealth, OldValue);
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
	float newHealth = GetHealth();

	if(Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		newHealth = FMath::Clamp(newHealth, 0.f, GetMaxHealth());
		SetHealth(newHealth);
	}

	//Log the attribute change for debugging purposes
	AActor* OwnerActor = nullptr;

	if (Data.Target.AbilityActorInfo.IsValid())
	{
		OwnerActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
	}

	UE_LOG(LogTemp, Warning, TEXT("Health changed: %s → %f"),
		OwnerActor ? *OwnerActor->GetName() : TEXT("Unknown"),
		newHealth
	);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			1.5f,
			FColor::Red,
			FString::Printf(TEXT("%s Health: %.1f"),
				OwnerActor ? *OwnerActor->GetName() : TEXT("Unknown"),
				newHealth)
		);
	}
}

void UGHAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UGHAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGHAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
}
