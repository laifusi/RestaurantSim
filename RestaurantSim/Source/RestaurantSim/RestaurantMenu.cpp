// Fill out your copyright notice in the Description page of Project Settings.


#include "RestaurantMenu.h"
#include "Ingredient.h"

// Sets default values
ARestaurantMenu::ARestaurantMenu()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARestaurantMenu::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARestaurantMenu::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FRecipe ARestaurantMenu::ChooseRandomRecipe() const
{
	if (Recipes.Num() <= 0)
		return FRecipe();

	int32 RandId = FMath::RandRange(0, Recipes.Num());
	return Recipes[RandId];
}

