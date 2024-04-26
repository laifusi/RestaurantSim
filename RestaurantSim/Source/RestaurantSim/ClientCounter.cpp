// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientCounter.h"
#include "Worker.h"
#include "Client.h"
#include "RestaurantGameMode.h"

void AClientCounter::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<ARestaurantGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->SetClientCounter(this);
	}
}

void AClientCounter::AddNewClient(AClient* NewClient)
{
	Clients.Add(NewClient);
}

void AClientCounter::NotifyWorker(AWorker* Worker, bool bIsOverlapping) const
{
	Super::NotifyWorker(Worker, bIsOverlapping);

	if (Clients.Num() > 0)
	{
		Worker->ClientCounterDetected(Clients[0]);
	}
	else
	{
		Worker->ClientCounterDetected(nullptr);
	}
}
