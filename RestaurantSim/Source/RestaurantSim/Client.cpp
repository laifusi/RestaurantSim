// Fill out your copyright notice in the Description page of Project Settings.


#include "Client.h"
#include "Ingredient.h"

// Sets default values
AClient::AClient()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AClient::BeginPlay()
{
	Super::BeginPlay();
}

void AClient::ChooseRecipe()
{
	if (RestaurantMenu)
	{
		DesiredSandwich = RestaurantMenu->ChooseRandomRecipe();
	}

	if (!RestaurantMenu || DesiredSandwich.Ingredients.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("DESTROYED CLIENT"));
		Destroy();
	}
}

void AClient::SetRestaurantMenu(ARestaurantMenu* NewRestaurantMenu)
{
	RestaurantMenu = NewRestaurantMenu;
}

TArray<TSubclassOf<AIngredient>> AClient::GetDesiredIngredients()
{
	return DesiredSandwich.Ingredients;
}

int32 AClient::GetDesiredSandwichPrice() const
{
	return DesiredSandwich.Price;
}

FText AClient::GetDesiredSandwichName() const
{
	return FText::FromString(DesiredSandwich.RecipeName);
}

// Called every frame
void AClient::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

