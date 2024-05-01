// Fill out your copyright notice in the Description page of Project Settings.


#include "SandwichObject.h"
#include "Ingredient.h"

// Sets default values
ASandwichObject::ASandwichObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASandwichObject::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASandwichObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASandwichObject::AddIngredient(TSubclassOf<AIngredient> Ingredient)
{
	if (Ingredient)
	{
		UE_LOG(LogTemp, Display, TEXT("Adding ingredient: %s"), *Ingredient->GetName());
		IncludedIngredients.Add(Ingredient);
		FVector Location = GetActorLocation();
		Location.Z += IncludedIngredients.Num() * IngredientOffset;
		AActor* SpawnedIngredient = GetWorld()->SpawnActor(Ingredient, &Location);
		if (SpawnedIngredient)
		{
			SpawnedIngredient->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		}
	}
}

TArray<TSubclassOf<AIngredient>> ASandwichObject::GetIngredients() const
{
	return IncludedIngredients;
}

