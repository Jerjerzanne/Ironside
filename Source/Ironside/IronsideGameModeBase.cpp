// Fill out your copyright notice in the Description page of Project Settings.


#include "IronsideGameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "PlayerCharacter.h"

AIronsideGameModeBase::AIronsideGameModeBase() 
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/SimplePlayerCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}