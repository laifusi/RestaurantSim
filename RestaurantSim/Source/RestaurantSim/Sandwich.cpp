// Fill out your copyright notice in the Description page of Project Settings.


#include "Sandwich.h"
#include "Ingredient.h"

// Sets default values
ASandwich::ASandwich()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASandwich::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASandwich::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASandwich::AddIngredient(TSubclassOf<class AIngredient> Ingredient)
{
	if (Ingredient)
	{
		UE_LOG(LogTemp, Display, TEXT("Adding ingredient: %s"), *Ingredient->GetName());
		IncludedIngredients.Add(Ingredient);
	}
}

