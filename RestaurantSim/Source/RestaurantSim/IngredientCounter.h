// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Counter.h"
#include "IngredientCounter.generated.h"

/**
 * 
 */
UCLASS()
class RESTAURANTSIM_API AIngredientCounter : public ACounter
{
	GENERATED_BODY()

private:

	UPROPERTY(EditInstanceOnly)
	TSubclassOf<class AIngredient> IngredientType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyWorker(class AWorker* Worker, bool bIsOverlapping, UPrimitiveComponent* OverlappedComponent) const override;
	
};
