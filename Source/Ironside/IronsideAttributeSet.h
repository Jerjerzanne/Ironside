// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "UnrealNetwork.h"
#include "AbilitySystemComponent.h"
#include "IronsideAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class IRONSIDE_API UIronsideAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
		// Constructors and overrides

		UIronsideAttributeSet();
		virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

		//Current Health
		UPROPERTY(Category = "Attributes", EditAnywhere, ReplicatedUsing = OnRep_Health, BlueprintReadOnly)
		FGameplayAttributeData Health;
		ATTRIBUTE_ACCESSORS(UIronsideAttributeSet, Health)

		//Max Health
		UPROPERTY(Category = "Attributes", EditAnywhere, ReplicatedUsing = OnRep_MaxHealth, BlueprintReadOnly)
		FGameplayAttributeData MaxHealth;
		ATTRIBUTE_ACCESSORS(UIronsideAttributeSet, MaxHealth)
		
		UFUNCTION()
		virtual void OnRep_Health();

		UFUNCTION()
		virtual void OnRep_MaxHealth();

	
};
