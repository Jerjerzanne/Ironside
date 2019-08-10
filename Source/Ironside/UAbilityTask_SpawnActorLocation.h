// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities\Tasks\AbilityTask.h"
#include "GameFramework/Actor.h"
#include "UAbilityTask_SpawnActorLocation.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSpawnActorDelegate, AActor*, SpawnedActor);

UCLASS()
class IRONSIDE_API UAbilityTask_SpawnActorLocation: public UAbilityTask
{
public:
	GENERATED_BODY()

	//The important bit here.
	UPROPERTY(BlueprintAssignable)
	FSpawnActorDelegate Success;

	UPROPERTY(BlueprintAssignable)
	FSpawnActorDelegate FailedToSpawn;

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "SpawnActorLocation", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		static UAbilityTask_SpawnActorLocation* CreateMyTask(UGameplayAbility* OwningAbility, TSubclassOf<AActor> Class, FTransform Transform);

	UFUNCTION(BlueprintCallable, meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"), Category = "Abilities")
		bool BeginSpawningActor(UGameplayAbility* OwningAbility, TSubclassOf<AActor> Class, AActor*& SpawnedActor);

	UFUNCTION(BlueprintCallable, meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"), Category = "Abilities")
		void FinishSpawningActor(UGameplayAbility* OwningAbility, AActor* SpawnedActor);

	FTransform SpawnTransform;

	/* This function will call after the BP node has successfully requested the
	ability task from the static function. You put your actual
	functionality here. More on that in a bit. */
	//virtual void Activate() override;
};


