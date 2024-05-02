// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Counter.h"
#include "ClientCounter.generated.h"

/**
 * 
 */
UCLASS()
class RESTAURANTSIM_API AClientCounter : public ACounter
{
	GENERATED_BODY()

public:
	void AddNewClient(class AClient* NewClient);
	void CheckSandwich(class ASandwichObject* Sandwich);
	void RemoveClient(AClient* CurrentClient);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyWorker(class AWorker* Worker, bool bIsOverlapping, UPrimitiveComponent* OverlappedComponent) const override;

private:
	UPROPERTY(VisibleInstanceOnly)
	TArray<AClient*> Clients;
	UPROPERTY(EditAnywhere)
	FVector ClientOffset;

	class ARestaurantGameMode* GameMode;
	void MoveQueueUp();
};
