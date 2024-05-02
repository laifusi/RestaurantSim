// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RestaurantMenu.h"
#include "Client.generated.h"

UCLASS()
class RESTAURANTSIM_API AClient : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClient();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ChooseRecipe();
	void SetRestaurantMenu(ARestaurantMenu* NewRestaurantMenu);
	TArray<TSubclassOf<class AIngredient>> GetDesiredIngredients();

	UFUNCTION(BlueprintPure)
	FText GetDesiredSandwichName() const;

private:
	UPROPERTY(VisibleInstanceOnly)
	FRecipe DesiredSandwich;

	UPROPERTY()
	ARestaurantMenu* RestaurantMenu;
};
