// Fill out your copyright notice in the Description page of Project Settings.

#include "Cop.h"
#include "UnrealMathUtility.h"
// Sets default values
ACop::ACop()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ACop::BeginPlay()
{
	Super::BeginPlay();
	//UPROPERTY(EditAnywhere)
	//body=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
}

// Called every frame
void ACop::Tick(float DeltaTime)
{
	float boundary = 400;
	Super::Tick(DeltaTime);
	Patrol(boundary, DeltaTime);
	SetActorTickInterval(0.0f);
	

}
void ACop::Patrol(float boundary, float DeltaTime)
{
	FTimerHandle WaitBeforeTurn;
	FVector NewLocation = GetActorLocation();
	if (Right)
	{
		NewLocation.X += (DeltaTime * 40.f);
		SetActorLocation(NewLocation);
		if (NewLocation.X > boundary)
		{
			Right = false;

			FRotator ActorRotation = this->GetActorRotation();
			ActorRotation.Yaw += 180;
			this->SetActorRotation(ActorRotation);
			float RandomWaitTime = FMath::RandRange(5, 30);
			UE_LOG(LogTemp, Warning, TEXT("MyCharacter's FName is %f"),RandomWaitTime);
			SetActorTickInterval(RandomWaitTime);
		}
	}

	else if (!Right)
	{
		
		NewLocation.X -= (DeltaTime * 40.f);
		SetActorLocation(NewLocation);
		if (NewLocation.X < -boundary)
		{
			Right = true;


			FRotator ActorRotation = this->GetActorRotation();
			ActorRotation.Yaw -= 180;
			this->SetActorRotation(ActorRotation);
			float RandomWaitTime = FMath::RandRange(5, 30);
			UE_LOG(LogTemp, Warning, TEXT("MyCharacter's mov is %f"), RandomWaitTime);
			SetActorTickInterval(RandomWaitTime);
			
		}
	}

}
