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
	if (Clients.Num() > 0 && Sandwich)
	{
		UE_LOG(LogTemp, Display, TEXT("CHECKING SANDWICH - We have clients"));
		GameMode->CheckSandwich(Sandwich, Clients[0]);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NO CLIENT OR SANDWICH"));
	}
}

void AClientCounter::RemoveClient(AClient* CurrentClient)
{
	Clients.Remove(CurrentClient);
	CurrentClient->Destroy();
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