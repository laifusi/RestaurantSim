// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SandwichObject.generated.h"

UCLASS()
class RESTAURANTSIM_API ASandwichObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASandwichObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddIngredient(TSubclassOf<class AIngredient> Ingredient);
	TArray<TSubclassOf<class AIngredient>> GetIngredients() const;
	void DestroySandwich();

private:
	UPROPERTY(VisibleAnywhere)
	TArray<TSubclassOf<AIngredient>> IncludedIngredients;
	UPROPERTY(VisibleAnywhere)
	TArray<AIngredient*> IncludedIngredientObjects;
	UPROPERTY(EditAnywhere)
	float IngredientOffset = 0.5;

};