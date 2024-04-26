// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Worker.generated.h"

UCLASS()
class RESTAURANTSIM_API AWorker : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWorker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void CounterDetected(TSubclassOf<class AIngredient> IngredientType);
	void LeftCounter(TSubclassOf<AIngredient> IngredientType);
	void EmptyCounterDetected(class ASandwichObject* Sandwich);
	void ClientCounterDetected(class AClient* Client);

private:
	UPROPERTY(EditAnywhere)
	float WalkSpeed = 100;
	UPROPERTY(EditAnywhere)
	float TurnSpeed = 100;

	UPROPERTY(VisibleInstanceOnly)
	TSubclassOf<AIngredient> DetectedIngredientType;
	UPROPERTY(VisibleInstanceOnly)
	TSubclassOf<AIngredient> PickedUpIngredient;
	UPROPERTY(VisibleInstanceOnly)
	bool bOnEmptyCounter;
	UPROPERTY(VisibleInstanceOnly)
	class ASandwichObject* DetectedSandwich;
	UPROPERTY(VisibleInstanceOnly)
	class ASandwichObject* PickedUpSandwich;
	UPROPERTY(VisibleInstanceOnly)
	bool bOnClientCounter;
	UPROPERTY(VisibleInstanceOnly)
	class AClient* DetectedClient;


	void WalkForward(float Value);
	void WalkRight(float Value);
	void TurnRight(float Value);
	void PickUp();
	void PutDown();

};
