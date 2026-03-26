// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GHSpellProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UGameplayEffect;
class UAbilitySystemComponent;

UCLASS()
class GHCOMBATPROTOTYPE_API AGHSpellProjectile : public AActor
{
	GENERATED_BODY()

public:
    AGHSpellProjectile();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
    TObjectPtr<USphereComponent> CollisionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
    TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

    /** Damage effect applied on hit */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
    TSubclassOf<UGameplayEffect> DamageEffectClass;

    /** lifespan in seconds */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
    float LifeSeconds = 3.0f;

    /** Actor that spawned this projectile */
    UPROPERTY()
    TObjectPtr<AActor> SourceActor;

    UFUNCTION()
    void OnProjectileOverlap(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );

    void ApplyDamageToTarget(AActor* TargetActor);
    void DestroyProjectile();

public:
    void InitializeProjectile(AActor* InSourceActor);

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
