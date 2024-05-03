// Fill out your copyright notice in the Description page of Project Settings.


#include "Worker.h"
#include "Kismet/GameplayStatics.h"
#include "Ingredient.h"
#include "SandwichObject.h"
#include "ClientCounter.h"
#include "EmptyCounter.h"
#include "Client.h"
#include "GameFramework/PlayerState.h"

// Sets default values
AWorker::AWorker()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TrayMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tray Mesh"));
	TrayMesh->SetupAttachment(RootComponent);
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
	PlayerInputComponent->BindAxis(TEXT("WalkRight"), this, &AWorker::WalkRight);
	PlayerInputComponent->BindAxis(TEXT("TurnRight"), this, &AWorker::TurnRight);
	PlayerInputComponent->BindAction(TEXT("PickUp"), EInputEvent::IE_Pressed, this, &AWorker::PickUp);
	PlayerInputComponent->BindAction(TEXT("PutDown"), EInputEvent::IE_Pressed, this, &AWorker::PutDown);
}

void AWorker::CounterDetected(TSubclassOf<AIngredient> IngredientType)
{
	DetectedIngredientType = IngredientType;
}

void AWorker::LeftCounter(TSubclassOf<AIngredient> IngredientType)
{
	if (DetectedIngredientType == IngredientType)
	{
		DetectedIngredientType = nullptr;
	}
}

void AWorker::EmptyCounterDetected(ASandwichObject* Sandwich, AEmptyCounter* EmptyCounter)
{
	bOnEmptyCounter = EmptyCounter != nullptr;
	DetectedEmptyCounter = EmptyCounter;
	DetectedSandwich = Sandwich;
}

void AWorker::ClientCounterDetected(AClientCounter* ClientCounter)
{
	bOnClientCounter = ClientCounter != nullptr;
	DetectedClientCounter = ClientCounter;
}

void AWorker::WalkForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value * WalkSpeed * UGameplayStatics::GetWorldDeltaSeconds(this));
}

void AWorker::WalkRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value * WalkSpeed * UGameplayStatics::GetWorldDeltaSeconds(this));
}

void AWorker::TurnRight(float Value)
{
	AddControllerYawInput(Value * TurnSpeed * UGameplayStatics::GetWorldDeltaSeconds(this));
}

void AWorker::PickUp()
{
	if (DetectedIngredientType)
	{
		UE_LOG(LogTemp, Warning, TEXT("INGREDIENT PICKED UP: %s"), *DetectedIngredientType.Get()->GetName());
		PickedUpIngredient = DetectedIngredientType;
	}
	else if (DetectedSandwich && DetectedEmptyCounter)
	{
		UE_LOG(LogTemp, Warning, TEXT("SANDWICH PICKED UP"));
		PickedUpSandwich = DetectedSandwich;
		DetectedEmptyCounter->TakeSandwich();
		PickedUpSandwich->AttachToComponent(TrayMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
}

void AWorker::PutDown()
{
	if (bOnEmptyCounter)
	{
		if (PickedUpIngredient)
		{
			if (!DetectedSandwich)
			{
				DetectedSandwich = DetectedEmptyCounter->CreateNewSandwich();
			}

			UE_LOG(LogTemp, Warning, TEXT("INGREDIENT PUT DOWN: %s"), *PickedUpIngredient.Get()->GetName());
			// Add the ingredient to the sandwich
			DetectedSandwich->AddIngredient(PickedUpIngredient);
			PickedUpIngredient = nullptr;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("NOT PUT DOWN: No Ingredient"), bOnEmptyCounter);
		}
	}
	else if(bOnClientCounter)
	{
		if (DetectedClientCounter && PickedUpSandwich)
		{
			UE_LOG(LogTemp, Warning, TEXT("GIVING SANDWICH: %s"), *PickedUpSandwich->GetName());
			UE_LOG(LogTemp, Warning, TEXT("TO CLIENT"));
			CheckSandwich(PickedUpSandwich, DetectedClientCounter->GetCurrentClient());
			PickedUpSandwich->DestroySandwich();
			PickedUpSandwich = nullptr;
		}
	}
}


void AWorker::CheckSandwich(ASandwichObject* Sandwich, AClient* CurrentClient)
{
	bool bIsCorrect = true;
	TArray<TSubclassOf<AIngredient>> SandwichIngredients = Sandwich->GetIngredients();
	TArray<TSubclassOf<AIngredient>> DesiredIngredients = CurrentClient->GetDesiredIngredients();

	if (DesiredIngredients.Num() == SandwichIngredients.Num())
	{
		for (int32 i = 0; i < DesiredIngredients.Num(); i++)
		{
			if (DesiredIngredients[i] != SandwichIngredients[i])
			{
				UE_LOG(LogTemp, Warning, TEXT("WRONG SANDWICH"));
				bIsCorrect = false;
				break;
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("WRONG AMOUNT OF INGREDIENTS"));
		bIsCorrect = false;
	}

	if (bIsCorrect)
	{
		int32 PointsWon = CurrentClient->GetDesiredSandwichPrice();
		AController* PlayerController = GetController();
		if (PlayerController)
		{
			APlayerState* State = PlayerController->GetPlayerState<APlayerState>();
			if (State)
			{
				State->Score += PointsWon;
			}
		}
	}

	DetectedClientCounter->RemoveClient(CurrentClient);
}

