// Fill out your copyright notice in the Description page of Project Settings.


#include "GHSpellProjectile.h"

// Sets default values
AGHSpellProjectile::AGHSpellProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGHSpellProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGHSpellProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

