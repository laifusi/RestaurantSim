// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Counter.generated.h"

UCLASS()
class RESTAURANTSIM_API ACounter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACounter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyWorker(class AWorker* Worker, bool bIsOverlapping, UPrimitiveComponent* OverlappedComponent) const;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* ColliderComp;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SpawnPoint;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnActorEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
