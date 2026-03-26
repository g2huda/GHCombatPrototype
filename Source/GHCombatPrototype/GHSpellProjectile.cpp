// Fill out your copyright notice in the Description page of Project Settings.

#include "GHSpellProjectile.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h" 
#include "GameplayEffect.h"

// Sets default values
AGHSpellProjectile::AGHSpellProjectile()
{
    PrimaryActorTick.bCanEverTick = false;

    bReplicates = true;
    SetReplicateMovement(true);

    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    RootComponent = CollisionComponent;

    CollisionComponent->InitSphereRadius(16.f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionObjectType(ECC_WorldDynamic);
    CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
    CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    CollisionComponent->SetGenerateOverlapEvents(true);

    ProjectileMovementComponent = 
        CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
    ProjectileMovementComponent->InitialSpeed = 1500.f;
    ProjectileMovementComponent->MaxSpeed = 1500.f;
    ProjectileMovementComponent->ProjectileGravityScale = 0.f;
    ProjectileMovementComponent->bRotationFollowsVelocity = true;
}

// Called when the game starts or when spawned
void AGHSpellProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGHSpellProjectile::OnProjectileOverlap(
    UPrimitiveComponent* OverlappedComponent, 
    AActor* OtherActor, 
    UPrimitiveComponent* OtherComp, 
    int32 OtherBodyIndex, 
    bool bFromSweep, 
    const FHitResult& SweepResult)
{
    if (!HasAuthority())
    {
        return;
    }

    if (!OtherActor || OtherActor == this || OtherActor == SourceActor)
    {
        return;
    }

    ApplyDamageToTarget(OtherActor);

    DestroyProjectile();
}

void AGHSpellProjectile::ApplyDamageToTarget(AActor* TargetActor)
{
    if (!DamageEffectClass || !TargetActor)
    {
        return;
    }

    UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(SourceActor);
    UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

    if (!TargetASC)
    {
        return;
    }

    FGameplayEffectContextHandle EffectContext;

    if (SourceASC)
    {
        EffectContext = SourceASC->MakeEffectContext();
        EffectContext.AddSourceObject(this);
    }
    else
    {
        EffectContext = TargetASC->MakeEffectContext();
        EffectContext.AddSourceObject(this);
    }

    FGameplayEffectSpecHandle EffectSpecHandle;

    if (SourceASC)
    {
        EffectSpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, 1.0f, EffectContext);
    }
    else
    {
        EffectSpecHandle = TargetASC->MakeOutgoingSpec(DamageEffectClass, 1.0f, EffectContext);
    }

    if (!EffectSpecHandle.IsValid())
    {
        return;
    }

    TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}

void AGHSpellProjectile::DestroyProjectile()
{
    if (HasAuthority())
    {
        Destroy();
    }
}

void AGHSpellProjectile::InitializeProjectile(AActor* InSourceActor)
{
    SourceActor = InSourceActor;

    // ignore collisions with the source actor
    if (SourceActor && CollisionComponent)
    {
        CollisionComponent->IgnoreActorWhenMoving(SourceActor, true);
    }
}

void AGHSpellProjectile::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

   // DOREPLIFETIME(AGHSpellProjectile, SourceActor);
}
