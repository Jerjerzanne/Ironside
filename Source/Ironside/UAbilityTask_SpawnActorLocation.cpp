// Fill out your copyright notice in the Description page of Project Settings.


#include "UAbilityTask_SpawnActorLocation.h"
#include "EngineGlobals.h"
#include "Engine/Engine.h"
#include "AbilitySystemComponent.h"

UAbilityTask_SpawnActorLocation* UAbilityTask_SpawnActorLocation::CreateMyTask(UGameplayAbility* OwningAbility, TSubclassOf<AActor> Class, FTransform Transform)
{

	UAbilityTask_SpawnActorLocation* MyObj = NewAbilityTask<UAbilityTask_SpawnActorLocation>(OwningAbility);
	//Just assume we have defined a float called OptionalValue somewhere in the class before. This is just an example.
	MyObj->SpawnTransform = Transform;

	return MyObj;
}

//void UAbilityTask_SpawnActorLocation::Activate()
//{
//	/* This is the part where you'd set up different delegates, timers etc. to prepare the task
//	to eventually broadcast OnCalled sometime later. We have nothing prepared in this tutorial
//	task however, so we may as well just call OnCalled right within the Activate function instead. */
//	OnCalled.Broadcast(FTransform());
//}

///

bool UAbilityTask_SpawnActorLocation::BeginSpawningActor(UGameplayAbility* OwningAbility, TSubclassOf<AActor> InClass, AActor*& SpawnedActor)
{
	if (Ability && Ability->GetCurrentActorInfo()->IsNetAuthority() && ShouldBroadcastAbilityTaskDelegates())
	{
		UWorld* const World = GEngine->GetWorldFromContextObject(OwningAbility, EGetWorldErrorMode::LogAndReturnNull);
		if (World)
		{
			SpawnedActor = World->SpawnActorDeferred<AActor>(InClass, SpawnTransform, NULL, NULL, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		}
	}

	if (SpawnedActor == nullptr)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			FailedToSpawn.Broadcast(nullptr);
		}
		return false;
	}

	return true;
}

void UAbilityTask_SpawnActorLocation::FinishSpawningActor(UGameplayAbility* OwningAbility, AActor* SpawnedActor)
{
	if (SpawnedActor)
	{
		bool bTransformSet = false;
		//FTransform SpawnTransform;
		//if (FGameplayAbilityTargetData * LocationData = CachedTargetDataHandle.Get(0))		//Hardcode to use data 0. It's OK if data isn't useful/valid.
		//{
		//	//Set location. Rotation is unaffected.
		//	if (LocationData->HasHitResult())
		//	{
		//		SpawnTransform.SetLocation(LocationData->GetHitResult()->Location);
		//		bTransformSet = true;
		//	}
		//	else if (LocationData->HasEndPoint())
		//	{
		//		SpawnTransform = LocationData->GetEndPointTransform();
		//		bTransformSet = true;
		//	}
		//}
		//if (!bTransformSet)
		//{
		//	SpawnTransform = AbilitySystemComponent->GetOwner()->GetTransform();
		//}

		SpawnedActor->FinishSpawning(SpawnTransform);

		if (ShouldBroadcastAbilityTaskDelegates())
		{
			Success.Broadcast(SpawnedActor);
		}
	}

	EndTask();
}

///