// Fill out your copyright notice in the Description page of Project Settings.


#include "EmptyCounter.h"
#include "Worker.h"
#include "SandwichObject.h"

// Called when the game starts or when spawned
void AEmptyCounter::BeginPlay()
{
	Super::BeginPlay();
}

void AEmptyCounter::NotifyWorker(AWorker* Worker, bool bIsOverlapping, UPrimitiveComponent* OverlappedComponent) const
{
	Super::NotifyWorker(Worker, bIsOverlapping, OverlappedComponent);

	UE_LOG(LogTemp, Warning, TEXT("EMPTY COUNTER"));
	if (OverlappedComponent)
	{
		AEmptyCounter* Counter = Cast<AEmptyCounter>(OverlappedComponent->GetAttachmentRootActor());
		if (Counter)
		{
			if (bIsOverlapping)
			{
				Worker->EmptyCounterDetected(Sandwich ? Sandwich : nullptr, Counter);
			}
			else
			{
				Worker->EmptyCounterDetected(nullptr, nullptr);
			}
		}
	}
}

ASandwichObject* AEmptyCounter::CreateNewSandwich()
{
	Sandwich = GetWorld()->SpawnActor<ASandwichObject>(SandwichClass);
	if (Sandwich)
	{
		Sandwich->AttachToComponent(SpawnPoint, FAttachmentTransformRules::KeepRelativeTransform);
	}
	return Sandwich;
}

void AEmptyCounter::TakeSandwich()
{
	Sandwich = nullptr;
}
