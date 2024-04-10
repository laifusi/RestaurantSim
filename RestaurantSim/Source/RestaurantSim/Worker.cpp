// Fill out your copyright notice in the Description page of Project Settings.


#include "Worker.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWorker::AWorker()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWorker::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWorker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWorker::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("WalkForward"), this, &AWorker::WalkForward);
	PlayerInputComponent->BindAxis(TEXT("WalkRight"), this, &AWorker::TurnRight);
}

void AWorker::WalkForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value * WalkSpeed * UGameplayStatics::GetWorldDeltaSeconds(this));
}

void AWorker::TurnRight(float Value)
{
	AddControllerYawInput(Value * TurnSpeed * UGameplayStatics::GetWorldDeltaSeconds(this));
}
