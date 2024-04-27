// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RestaurantGameMode.generated.h"

/**
 * 
 */
UCLASS()
class RESTAURANTSIM_API ARestaurantGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void SetClientCounter(class AClientCounter* NewClientCounter);
	void CheckSandwich(class ASandwichObject* Sandwich, class AClient* CurrentClient);
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AClient> ClientClass;
	UPROPERTY(EditAnywhere)
	float StartClientSpawn = 2;
	UPROPERTY(EditAnywhere)
	float ClientSpawnRate = 10;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ARestaurantMenu> RestaurantMenuClass;
	ARestaurantMenu* RestaurantMenu;
	AClientCounter* ClientCounter;

	void SpawnClient();
};
