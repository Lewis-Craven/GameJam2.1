// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimonSays.generated.h"

// Enum for game state
UENUM(BlueprintType)
enum class ESimonState : uint8
{
    Showing     UMETA(DisplayName = "Showing Sequence"),
    WaitingForInput UMETA(DisplayName = "Waiting For Input"),
    GameOver    UMETA(DisplayName = "Game Over")
};

// Enum for button types
UENUM(BlueprintType)
enum class ESimonButtonType : uint8
{
    Red,
    Blue,
    Yellow,
    Green
};

UCLASS()
class MYPROJECT_API ASimonSays : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ASimonSays();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Variable

    // The current Simon sequence
    UPROPERTY(BlueprintReadOnly, Category = "Simon")
    TArray<ESimonButtonType> Sequence;

    // Current player input index
    UPROPERTY(BlueprintReadOnly, Category = "Simon")
    int32 currentInputIndex;

    // Number of buttons available in the game (for random generation)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Simon")
    int32 buttonCount;


    // Current game state
    UPROPERTY(BlueprintReadOnly, Category = "Simon")
    ESimonState SimonState;

    // Timer to play sequence step-by-step
    FTimerHandle SequenceTimer;
    FTimerHandle RoundWonTimer;

    // Index for current step while playing sequence
    int32 PlayIndex;

    // Delay between each step when playing sequence
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Simon")
    float StepDelay;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Simon")
    float RoundWonDelay;


    // Current step being shown
    UPROPERTY(BlueprintReadOnly, Category = "Simon")
    ESimonButtonType Step;



    // C++ Functions

    // Start or reset the game
    UFUNCTION(BlueprintCallable, Category = "Simon")
    void startGame();

    UFUNCTION(BlueprintCallable, Category = "Simon")
    void addNewStep();


    UFUNCTION(BlueprintCallable, Category = "Simon")
    void generateRandomSequence(int32 Length);


    UFUNCTION(BlueprintCallable, Category = "Simon")
    void registerInput(ESimonButtonType buttonIndex);

  
    UFUNCTION(BlueprintCallable, Category = "Simon")
    void resetGame();

    UFUNCTION(BlueprintCallable, Category = "Simon")
    void playSequence();

    UFUNCTION(BlueprintCallable, Category = "Simon")
    void playNextStep();

    UFUNCTION(BlueprintCallable, Category = "Simon")
    void startNextRound();



	// Blueprint Events

    UFUNCTION(BlueprintImplementableEvent, Category = "Simon")
    void glowButton();

    UFUNCTION(BlueprintImplementableEvent, Category = "Simon")
    void onRoundWon();
    
    UFUNCTION(BlueprintImplementableEvent, Category = "Simon")
    void onGameOver();

    UFUNCTION(BlueprintImplementableEvent, Category = "Simon")
    void mouseCursor();
};
