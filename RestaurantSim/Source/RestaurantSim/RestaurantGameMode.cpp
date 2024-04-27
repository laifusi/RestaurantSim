// Fill out your copyright notice in the Description page of Project Settings.


#include "RestaurantGameMode.h"
#include "TimerManager.h"
#include "Client.h"
#include "RestaurantMenu.h"
#include "ClientCounter.h"
#include "SandwichObject.h"
#include "Ingredient.h"

void ARestaurantGameMode::BeginPlay()
{
	Super::BeginPlay();

	RestaurantMenu = GetWorld()->SpawnActor<ARestaurantMenu>(RestaurantMenuClass);

	FTimerHandle ClientSpawnTimer;
	GetWorldTimerManager().SetTimer(ClientSpawnTimer, this, &ARestaurantGameMode::SpawnClient, ClientSpawnRate, true, StartClientSpawn);

}

void ARestaurantGameMode::SetClientCounter(AClientCounter* NewClientCounter)
{
	ClientCounter = NewClientCounter;
}

void ARestaurantGameMode::CheckSandwich(ASandwichObject* Sandwich, AClient* CurrentClient)
{
	bool bIsCorrect = true;
	TArray<TSubclassOf<AIngredient>> SandwichIngredients = Sandwich->GetIngredients();
	TArray<TSubclassOf<AIngredient>> DesiredIngredients = CurrentClient->GetDesiredIngredients();
	for (int32 i = 0; i < DesiredIngredients.Num(); i++)
	{
		if (DesiredIngredients[i] != SandwichIngredients[i])
		{
			UE_LOG(LogTemp, Warning, TEXT("WRONG SANDWICH"));
			bIsCorrect = false;
			break;
		}
	}

	if (bIsCorrect)
	{
		//DESTROY CLIENT
	}
}

void ARestaurantGameMode::SpawnClient()
{
	AClient* NewClient = GetWorld()->SpawnActor<AClient>(ClientClass);
	NewClient->SetRestaurantMenu(RestaurantMenu);
	NewClient->ChooseRecipe();
	if (ClientCounter)
	{
		ClientCounter->AddNewClient(NewClient);
	}
}
