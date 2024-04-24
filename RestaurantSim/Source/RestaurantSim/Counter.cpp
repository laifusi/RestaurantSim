// Fill out your copyright notice in the Description page of Project Settings.


#include "Counter.h"
#include "Components/BoxComponent.h"
#include "Ingredient.h"
#include "Worker.h"
#include "SandwichObject.h"

// Sets default values
ACounter::ACounter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetupAttachment(RootComponent);

	ColliderComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	ColliderComp->SetupAttachment(StaticMesh);

}

// Called when the game starts or when spawned
void ACounter::BeginPlay()
{
	Super::BeginPlay();
	
	ColliderComp->OnComponentBeginOverlap.AddDynamic(this, &ACounter::OnActorOverlap);
	ColliderComp->OnComponentEndOverlap.AddDynamic(this, &ACounter::OnActorEndOverlap);
}

// Called every frame
void ACounter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACounter::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AWorker* Worker = Cast<AWorker>(OtherActor);
	if (Worker)
	{
		NotifyWorker(Worker, true);
	}
}

void ACounter::OnActorEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AWorker* Worker = Cast<AWorker>(OtherActor);
	if (Worker)
	{
		NotifyWorker(Worker, false);
	}
}

void ACounter::NotifyWorker(AWorker* Worker, bool bIsOverlapping) const
{
	UE_LOG(LogTemp, Display, TEXT("Notifying Worker"));
}

