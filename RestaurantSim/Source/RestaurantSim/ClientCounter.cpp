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
	if (NewClient)
	{
		Clients.Add(NewClient);
		// THIS CAN BE REFACTORED - DUPLICATED CODE??
		FVector Location = SpawnPoint->GetComponentLocation() + Clients.Num() * ClientOffset;
		NewClient->SetActorLocationAndRotation(Location, SpawnPoint->GetComponentQuat());
		//
		NewClient->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	}
}

void AClientCounter::RemoveClient(AClient* CurrentClient)
{
	Clients.Remove(CurrentClient);
	CurrentClient->Destroy();
	MoveQueueUp();
}

AClient* AClientCounter::GetCurrentClient() const
{
	return Clients.Num() > 0 ? Clients[0] : nullptr;
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

void AClientCounter::MoveQueueUp()
{
	for (int32 i = 0; i < Clients.Num(); i++)
	{
		// THIS CAN BE REFACTORED - DUPLICATED CODE??
		FVector Location = SpawnPoint->GetComponentLocation() + (i+1) * ClientOffset;
		Clients[i]->SetActorLocation(Location);
	}
}
