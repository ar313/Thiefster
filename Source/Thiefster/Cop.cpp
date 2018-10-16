// Fill out your copyright notice in the Description page of Project Settings.

#include "Cop.h"
#include "UnrealMathUtility.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Engine/Public/DelayAction.h"
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
	
	
	if(!IsRotating)Patrol(boundary, DeltaTime);
	
	
	if (IsRotating) {
		FTimerHandle TimerHandle;
		FTimerDelegate TimerDelayed;
		TimerDelayed.BindUFunction(this, FName("Rotate"),180, DeltaTime);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle,TimerDelayed,0.3f, false);
		
	}

}
void ACop::Patrol(float boundary, float DeltaTime)
{
	
	FTimerManager WaitBeforeTurn;
	FVector NewLocation = GetActorLocation();
	if (Right)
	{
		NewLocation.X += (DeltaTime * 40.f); //todo set speed
		SetActorLocation(NewLocation);
		if (NewLocation.X > boundary)
		{
			Right = false;
			IsRotating = true;
			

		}
	}

	else if (!Right)
	{
		
		
		NewLocation.X -= (DeltaTime * 40.f);   //todo set speed 
		SetActorLocation(NewLocation);
		if (NewLocation.X < -boundary)
		{
			Right = true;
			IsRotating = true;
			
			
		}
	}

}

void ACop::Rotate(float RotateDirection,float DeltaTime) {
	
		FRotator ActorRotation = this->GetActorRotation();
		if (Right)
		{
			ActorRotation.Yaw = RotateDirection-180.0f;
			this->SetActorRotation(FMath::RInterpConstantTo(GetActorRotation(), ActorRotation, DeltaTime*6, 5.f)); // todo set rotationspeed
		}
		if (!Right)
		{
			ActorRotation.Yaw = RotateDirection;
			this->SetActorRotation(FMath::RInterpConstantTo(GetActorRotation(), ActorRotation,DeltaTime*6,5.f));  // todo set rotationspeed
			
		}
		
		if ((FMath::Abs(FMath::RoundHalfFromZero(GetActorRotation().Yaw))) == (FMath::Abs(FMath::RoundHalfFromZero(ActorRotation.Yaw))))   
		{
			FRotator Normalise = this->GetActorRotation();
			Normalise.Yaw = FMath::RoundHalfToEven(Normalise.Yaw);
			this->SetActorRotation(Normalise);
			IsRotating = false;
		}
		UE_LOG(LogTemp, Log, TEXT("get Actor Rotation %f"), GetActorRotation().Yaw);
		UE_LOG(LogTemp, Log, TEXT("set Actor Rotation %f"), ActorRotation.Yaw);
		//if ((FMath::RoundHalfToZero(ActorRotation.Yaw) == 0) || FMath::RoundHalfFromZero(ActorRotation.Yaw)>=359)
		//{
		//	ActorRotation.Yaw = 0.001f;
			//this->SetActorRotation(ActorRotation);
	//	}
		//IsRotating = false;
	
}
