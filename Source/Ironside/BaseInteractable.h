// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseInteractable.generated.h"

UCLASS()
class IRONSIDE_API ABaseInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseInteractable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool RespondInteract(AActor* Player);
	bool RespondInteract_Implementation(AActor* Player);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FString InteractMessage();
	FString InteractMessage_Implementation();
};


