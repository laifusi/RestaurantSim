// Fill out your copyright notice in the Description page of Project Settings.


#include "IngredientCounter.h"
#include "Worker.h"
#include "Ingredient.h"

void AIngredientCounter::NotifyWorker(AWorker* Worker, bool bIsOverlapping) const
{
	Super::NotifyWorker(Worker, bIsOverlapping);

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
