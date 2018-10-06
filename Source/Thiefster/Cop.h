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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//UPROPERTY(EditAnywhere)
	//UStaticMeshComponent *body;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	void Patrol(float boundary,float DeltaTime);
	

};
