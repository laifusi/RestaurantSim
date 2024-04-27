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

void AClientCounter::CheckSandwich(ASandwichObject* Sandwich)
{
	GameMode->CheckSandwich(Sandwich, Clients[0]);
}

void AClientCounter::NotifyWorker(AWorker* Worker, bool bIsOverlapping, UPrimitiveComponent* OverlappedComponent) const
{
	Super::NotifyWorker(Worker, bIsOverlapping, OverlappedComponent);

	bool bIsDetected = bIsOverlapping && Clients.Num() > 0;
	
	if (OverlappedComponent)
	{
		AClientCounter* Counter = Cast<AClientCounter>(OverlappedComponent->GetAttachmentRootActor());
		if (Counter)
		{
			Worker->ClientCounterDetected(bIsDetected ? Counter : nullptr);
		}
	}
}
