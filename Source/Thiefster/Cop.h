// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cop.generated.h"

UCLASS()
class THIEFSTER_API ACop : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACop();
	bool Right = true;
	bool IsRotating = false;
	bool first = true;
	float WaitTime;
	FTimerHandle WaitForTime;
	float boundary;
	float MinStep;
	//UStaticMeshComponent* body;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime);
	UFUNCTION()
	void Rotate(float RotationDirection,float DeltaTime);
private:
	UFUNCTION()
	void Patrol(float DeltaTime);
	
};
