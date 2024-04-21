// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Counter.h"
#include "EmptyCounter.generated.h"

/**
 * 
 */
UCLASS()
class RESTAURANTSIM_API AEmptyCounter : public ACounter
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ASandwich> SandwichClass;

	UPROPERTY(VisibleInstanceOnly)
	ASandwich* Sandwich;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyWorker(class AWorker* Worker, bool bIsOverlapping) const override;
	
};
