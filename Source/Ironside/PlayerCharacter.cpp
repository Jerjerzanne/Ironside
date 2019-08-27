// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/InputComponent.h"
#include "AbilitySystemComponent.h"
#include "IronsideAttributeSet.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"


/*
-----------------------------
BEGIN PLAY, TICK AND CONSTRUCTOR
-----------------------------
*/

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Our ability system component.
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
	AttributeSet = CreateDefaultSubobject<UIronsideAttributeSet>(TEXT("AttributeSet"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (AbilitySystem)
	{
		FGameplayAbilityActorInfo* actorInfo = new FGameplayAbilityActorInfo();
		actorInfo->InitFromActor(this, this, AbilitySystem);
		AbilitySystem->AbilityActorInfo = TSharedPtr<FGameplayAbilityActorInfo>(actorInfo);
		
		

		if (HasAuthority())
		{
			//AbilitySystem->GiveAbility(FGameplayAbilitySpec(Ability.GetDefaultObject(), 1, 0));
			for (size_t i = 0; i < sizeof(AbilityArray); i++)
			{
				if (AbilityArray.IsValidIndex(i)) 
				{
					AbilitySystem->GiveAbility(FGameplayAbilitySpec(AbilityArray[i].GetDefaultObject(), 1, i));
				}
			}
		}
		AbilitySystem->InitAbilityActorInfo(this, this);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/*
-------------------------------
MANAGING INPUTS FOR MOVEMENT AND ABILITIES
-------------------------------
*/

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// set up gameplay key bindings
	check(PlayerInputComponent);
	// Bind movement events

	//PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	//PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	AbilitySystem->BindAbilityActivationToInputComponent(PlayerInputComponent, FGameplayAbilityInputBinds("ConfirmInput", "CancelInput", "AbilityInput"));
}

void APlayerCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(FVector(1, 0, 0), Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(FVector(0, 1, 0), Value);
	}
}

/*
------------------------------
GAMEPLAY ABILITY FUNCTIONS
------------------------------
*/

float APlayerCharacter::GetHealth() const
{
	return AttributeSet->GetHealth();
}

float APlayerCharacter::GetMaxHealth() const
{
	return AttributeSet->GetMaxHealth();
}


float APlayerCharacter::GetMovementSpeed() const
{
	return AttributeSet->GetMovementSpeed();
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystem->RefreshAbilityActorInfo();
}

void APlayerCharacter::HandleHealthChanged(float delta) 
{
	OnHealthChanged(delta);
}

void APlayerCharacter::HandleHandleMovementSpeedChanged(float delta)
{
	OnMovementSpeedChanged(delta);
}


void APlayerCharacter::GetAbilityCooldown()
{
	//FGameplayEffectQuery const Query = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(CooldownTags);
	//TArray<TPair<float, float>> TimeRemainingDuration = AbilitySystem->GetActiveEffectsTimeRemainingAndDuration();
	for (size_t i = 0; i < sizeof(AbilityArray); i++)
	{
		if (AbilityArray.IsValidIndex(i))
		{
			UGameplayEffect* effect = AbilityArray[i].GetDefaultObject()->GetCooldownGameplayEffect();
			if (effect != NULL)
			{
				FGameplayTagContainer* EffectCooldownTag = &effect->InheritableOwnedTagsContainer.CombinedTags;
				GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, effect->GetName());
			}
		}
	}
	
}