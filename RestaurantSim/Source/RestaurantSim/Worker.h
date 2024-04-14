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
	void EmptyCounterDetected(bool Detected);
	void LeftCounter(TSubclassOf<AIngredient> IngredientType);

private:
	UPROPERTY(EditAnywhere)
	float WalkSpeed = 100;
	UPROPERTY(EditAnywhere)
	float TurnSpeed = 100;

	UPROPERTY(VisibleInstanceOnly)
	TSubclassOf<AIngredient> DetectedIngredientType;
	UPROPERTY(VisibleInstanceOnly)
	bool bOnEmptyCounter;

	void WalkForward(float Value);
	void WalkRight(float Value);
	void TurnRight(float Value);

};
