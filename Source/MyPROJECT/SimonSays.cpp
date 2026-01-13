// Fill out your copyright notice in the Description page of Project Settings.

#include "SimonSays.h"
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
	PlayIndex = 0;
	StepDelay = 0.8f;
	
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

	// debug on length
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, FString::Printf(TEXT("Sequence length %d"), Sequence.Num()));
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
		// checked what button was pressed
		GEngine->AddOnScreenDebugMessage(
			-1,
			1.5f,
			FColor::Blue,
			FString::Printf(TEXT("Input %d: %s"),
				currentInputIndex,
				*UEnum::GetValueAsString(buttonIndex))
		);

		// Correct input
		currentInputIndex++;

		// Check if the sequence is complete
		if (currentInputIndex >= Sequence.Num())
		{
			onRoundWon();
			// Prepare for next round - generate a different sequence (increase length by 1)
			currentInputIndex = 0;
			generateRandomSequence(Sequence.Num() + 1);
			playSequence();
		}
	}
	else
	{
		// Incorrect input
		SimonState = ESimonState::GameOver;
		onGameOver();
	}
	
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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Playing sequence"));
}

void ASimonSays::playNextStep()
{
	if (PlayIndex >= Sequence.Num())
	{
		GetWorldTimerManager().ClearTimer(SequenceTimer);
		SimonState = ESimonState::WaitingForInput;
		return;
	}

	Step = Sequence[PlayIndex];

	// DEBUG PRINT (ONE AT A TIME)
	GEngine->AddOnScreenDebugMessage(
		-1,
		1.5f,
		FColor::Green,
		FString::Printf(TEXT("Step %d: %s"),
			PlayIndex,
			*UEnum::GetValueAsString(Step))
	);

	glowButton();
	PlayIndex++;
}



