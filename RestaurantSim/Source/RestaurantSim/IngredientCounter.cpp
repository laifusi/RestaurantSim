// Fill out your copyright notice in the Description page of Project Settings.


#include "IngredientCounter.h"
#include "Worker.h"
#include "Ingredient.h"
#include "DrawDebugHelpers.h"

AIngredientCounter::AIngredientCounter()
{
	IngredientSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Ingredient Spawn Point"));
	IngredientSpawnPoint->SetupAttachment(StaticMesh);
}

void AIngredientCounter::BeginPlay()
{
	Super::BeginPlay();

	if (IngredientType && IngredientSpawnPoint)
	{
		AIngredient* Ingredient = GetWorld()->SpawnActor<AIngredient>(IngredientType);
		Ingredient->AttachToComponent(IngredientSpawnPoint, FAttachmentTransformRules::KeepRelativeTransform);
	}
}

void AIngredientCounter::NotifyWorker(AWorker* Worker, bool bIsOverlapping, UPrimitiveComponent* OverlappedComponent) const
{
	Super::NotifyWorker(Worker, bIsOverlapping, OverlappedComponent);

	if (IngredientType)
	{
		if (bIsOverlapping)
		{
			Worker->CounterDetected(IngredientType);
		}
		else
		{
			Worker->LeftCounter(IngredientType);
		}
	}
}
