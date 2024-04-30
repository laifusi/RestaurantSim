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
	TSubclassOf<class ASandwichObject> SandwichClass;

	UPROPERTY(VisibleInstanceOnly)
	ASandwichObject* Sandwich;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyWorker(class AWorker* Worker, bool bIsOverlapping, UPrimitiveComponent* OverlappedComponent) const override;
	
public:
	class ASandwichObject* CreateNewSandwich();
	void TakeSandwich();
};
