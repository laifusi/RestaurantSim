// Fill out your copyright notice in the Description page of Project Settings.


#include "RestaurantGameMode.h"
#include "TimerManager.h"
#include "Client.h"
#include "RestaurantMenu.h"
#include "ClientCounter.h"

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
