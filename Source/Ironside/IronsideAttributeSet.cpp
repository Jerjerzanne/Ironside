// Fill out your copyright notice in the Description page of Project Settings.


#include "IronsideAttributeSet.h"
#include "UnrealNetwork.h"


UIronsideAttributeSet::UIronsideAttributeSet() 
{
	Health.SetBaseValue(100.0f);


}

void UIronsideAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UIronsideAttributeSet, Health);
}

void UIronsideAttributeSet::OnRep_Health()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UIronsideAttributeSet, Health);
}