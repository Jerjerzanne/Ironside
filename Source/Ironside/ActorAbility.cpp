// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorAbility.h"
#include "AbilitySystemComponent.h"

// Sets default values
AActorAbility::AActorAbility()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
}

// Called when the game starts or when spawned
void AActorAbility::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActorAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

