// Fill out your copyright notice in the Description page of Project Settings.


#include "EmptyCounter.h"
#include "Worker.h"
#include "SandwichObject.h"

// Called when the game starts or when spawned
void AEmptyCounter::BeginPlay()
{
	Super::BeginPlay();

	Sandwich = GetWorld()->SpawnActor<ASandwichObject>(SandwichClass);
}

void AEmptyCounter::NotifyWorker(AWorker* Worker, bool bIsOverlapping, UPrimitiveComponent* OverlappedComponent) const
{
	Super::NotifyWorker(Worker, bIsOverlapping, OverlappedComponent);

	Worker->EmptyCounterDetected(bIsOverlapping ? Sandwich : nullptr);
}
