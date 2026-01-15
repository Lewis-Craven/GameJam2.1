// Fill out your copyright notice in the Description page of Project Settings.

#include "SimonSays.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASimonSays::ASimonSays()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	buttonCount = 4;
	currentInputIndex = 0;
	SimonState = ESimonState::Showing;
	SequenceTimer = FTimerHandle();
	RoundWonTimer = FTimerHandle();
	PlayIndex = 0;
	StepDelay = 0.7f; 
	RoundWonDelay = 1.0f;
	
}

// Called when the game starts or when spawned
void ASimonSays::BeginPlay()
{
	Super::BeginPlay();
	
	
	startGame();

}

// Called every frame
void ASimonSays::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASimonSays::startGame()
{
	// Reset sequence and input tracking
	Sequence.Empty();
	currentInputIndex = 0;
	mouseCursor();
	// Generate an initial sequence (length 1)
	generateRandomSequence(1);

	playSequence();


}

void ASimonSays::addNewStep()
{
	// Generate a random index in the valid range and add exactly one new step
	int32 RandIndex = UKismetMathLibrary::RandomIntegerInRange(0, buttonCount - 1);
	ESimonButtonType NewStep = static_cast<ESimonButtonType>(RandIndex);

	Sequence.Add(NewStep);

}

void ASimonSays::generateRandomSequence(int32 Length)
{
	// prevent the same sequence from being generated again
	Sequence.Empty();
	if (Length <= 0)
	{
		return;
	}

	for (int32 i = 0; i < Length; ++i)
	{
		int32 RandIndex = UKismetMathLibrary::RandomIntegerInRange(0, buttonCount - 1);
		ESimonButtonType NewStep = static_cast<ESimonButtonType>(RandIndex);
		Sequence.Add(NewStep);
	}


}

void ASimonSays::registerInput(ESimonButtonType buttonIndex)
{
	if (SimonState != ESimonState::WaitingForInput)
	{
		return;
	}

	
	// Check if the input matches the expected step
	if (buttonIndex == Sequence[currentInputIndex])
	{
		

		// Correct input
		currentInputIndex++;

		// Check if the sequence is complete
		if (currentInputIndex >= Sequence.Num())
		{
			
			mouseCursor();
			onRoundWon();

			GetWorldTimerManager().SetTimer(
				RoundWonTimer,
				this,
				&ASimonSays::startNextRound,
				RoundWonDelay,
				false
			);
		}
	}
	else
	{
		// Incorrect input
		SimonState = ESimonState::GameOver;
		onGameOver();
	}

}

void ASimonSays::startNextRound()
{
	GetWorldTimerManager().ClearTimer(RoundWonTimer);
	currentInputIndex = 0;
	generateRandomSequence(Sequence.Num() + 1);

	playSequence();

}
void ASimonSays::resetGame()
{
	startGame();
}


void ASimonSays::playSequence()
{

	SimonState = ESimonState::Showing;
	PlayIndex = 0;
	// Set timer to play each step in the sequence
	GetWorldTimerManager().ClearTimer(SequenceTimer);
	GetWorldTimerManager().SetTimer(
		SequenceTimer,
		this,
		&ASimonSays::playNextStep,
		StepDelay, // Time between steps
		true
	);
	
}

void ASimonSays::playNextStep()
{
	if (PlayIndex >= Sequence.Num())
	{
		GetWorldTimerManager().ClearTimer(SequenceTimer);
		SimonState = ESimonState::WaitingForInput;
		mouseCursor();
		return;
	}

	Step = Sequence[PlayIndex];

	glowButton();
	PlayIndex++;
}

