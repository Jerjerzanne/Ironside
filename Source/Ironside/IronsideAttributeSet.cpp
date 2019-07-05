// Fill out your copyright notice in the Description page of Project Settings.


#include "IronsideAttributeSet.h"
#include "UnrealNetwork.h"
#include "PlayerCharacter.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"


UIronsideAttributeSet::UIronsideAttributeSet() 
{
	MaxHealth.SetBaseValue(100.0f);
	MaxHealth.SetCurrentValue(100.0f);
}

void UIronsideAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UIronsideAttributeSet, Health);
}

void UIronsideAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();

	// Compute the delta between old and new, if it is available
	float DeltaValue = 0;
	if (Data.EvaluatedData.ModifierOp == EGameplayModOp::Type::Additive)
	{
		// If this was additive, store the raw delta value to be passed along later
		DeltaValue = Data.EvaluatedData.Magnitude;
	}

	// Get the Target actor, which should be our owner
	AActor* TargetActor = nullptr;
	AController* TargetController = nullptr;
	APlayerCharacter* TargetCharacter = nullptr;
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		TargetCharacter = Cast<APlayerCharacter>(TargetActor);
	}

	// Get the Source actor
	AActor* AttackingActor = nullptr;
	AController* AttackingController = nullptr;
	AController* AttackingPlayerController = nullptr;
	if (Source && Source->AbilityActorInfo.IsValid() && Source->AbilityActorInfo->AvatarActor.IsValid())
	{
		AttackingActor = Source->AbilityActorInfo->AvatarActor.Get();
		AttackingController = Source->AbilityActorInfo->PlayerController.Get();
		AttackingPlayerController = Source->AbilityActorInfo->PlayerController.Get();
		if (AttackingController == nullptr && AttackingActor != nullptr)
		{
			if (APawn * Pawn = Cast<APawn>(AttackingActor))
			{
				AttackingController = Pawn->GetController();
			}
		}
	}

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// Handle other health changes such as from healing or direct modifiers
		// First clamp it
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));

		if (TargetCharacter)
		{
			// Call for all health changes
			TargetCharacter->HandleHealthChanged(DeltaValue);
		}
	}
}

void UIronsideAttributeSet::OnRep_Health()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UIronsideAttributeSet, Health);
}

void UIronsideAttributeSet::OnRep_MaxHealth()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UIronsideAttributeSet, MaxHealth);
}