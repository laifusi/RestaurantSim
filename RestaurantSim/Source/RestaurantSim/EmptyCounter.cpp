// Fill out your copyright notice in the Description page of Project Settings.


#include "EmptyCounter.h"
#include "Worker.h"
#include "Sandwich.h"

// Called when the game starts or when spawned
void AEmptyCounter::BeginPlay()
{
	Super::BeginPlay();

	Sandwich = GetWorld()->SpawnActor<ASandwich>(SandwichClass);
}

void AEmptyCounter::NotifyWorker(AWorker* Worker, bool bIsOverlapping) const
{
	Super::NotifyWorker(Worker, bIsOverlapping);

	Worker->EmptyCounterDetected(bIsOverlapping ? Sandwich : nullptr);
}
