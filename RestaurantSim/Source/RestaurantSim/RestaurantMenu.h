// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RestaurantMenu.generated.h"

USTRUCT()
struct FRecipe
{
	GENERATED_BODY()

	FRecipe() {}

	UPROPERTY(EditAnywhere)
	FString RecipeName;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<class AIngredient>> Ingredients;

	UPROPERTY(EditInstanceOnly)
	bool bIsAvailable;
};

UCLASS()
class RESTAURANTSIM_API ARestaurantMenu : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARestaurantMenu();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	TArray<FRecipe> Recipes;

};
