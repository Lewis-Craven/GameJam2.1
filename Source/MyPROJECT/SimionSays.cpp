// Fill out your copyright notice in the Description page of Project Settings.


#include "SimionSays.h"

// Sets default values
ASimionSays::ASimionSays()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASimionSays::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is AdventureGameMode!"));
	nextRound();

}

// Called every frame
void ASimionSays::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASimionSays::playSimonSaysSequence()
{

}

void ASimionSays::nextRound()
{
	Playerindex = 0;
	int32 newStep = FMath::RandRange(0, 3);

	for (int32 step : simonSaysSequence)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Simon"));
	}

}

void ASimionSays::resetGame()
{
}

