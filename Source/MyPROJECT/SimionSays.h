// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimionSays.generated.h"

UCLASS()
class MYPROJECT_API ASimionSays : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimionSays();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	void playSimonSaysSequence();
	void nextRound();
	void resetGame();

private:
	UPROPERTY(EditAnywhere)
	int32 Numbuttons = 4;

	TArray<int32> simonSaysSequence;
	int32 Playerindex = 0;
};
