// Fill out your copyright notice in the Description page of Project Settings.

#include "Cop.h"
#include "UnrealMathUtility.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h "
//#include  	"Runtime/Engine/Classes/Engine/StaticMesh.h"

// Sets default values
ACop::ACop()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	UObject* Cube = StaticLoadObject(UObject::StaticClass(), nullptr, TEXT("/Game/Cylinder")); //todo Set Police Mesh Path
	body->SetStaticMesh(Cast<UStaticMesh>(Cube));
	
	
}

// Called when the game starts or when spawned
void ACop::BeginPlay()
{  //todo Spawn Position;
	Super::BeginPlay();
	FVector SpawnPos = GetActorLocation();
	SpawnPos.Z = 90;
	this->SetActorLocation(SpawnPos);
	

	boundary = 400.0f;
	MinStep = 100.0f;
}

// Called every frame
void ACop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
	if (!IsRotating)
	{
		if (first) {
			GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
			WaitTime = FMath::FRandRange(0.4f, 7.0f);
			first = false;

		}
		FTimerHandle TimerHandle;
		FTimerDelegate TimerDelayed;
		TimerDelayed.BindUFunction(this, FName("Patrol"), DeltaTime);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelayed, WaitTime, false);
	//	Patrol(DeltaTime);

		
	}
	
	if (IsRotating) {
		
		if (first) {
			GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
			 WaitTime = FMath::FRandRange(0.4f, 7.0f); 
			first = false;
			
		}
		FTimerHandle TimerHandle;
		FTimerDelegate TimerDelayed;
		TimerDelayed.BindUFunction(this, FName("Rotate"),180.0f, DeltaTime);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle,TimerDelayed,WaitTime, false);
		
	}

}
void ACop::Patrol(float DeltaTime)
{
	
	FTimerManager WaitBeforeTurn;
	FVector NewLocation = GetActorLocation();
	if (Right)
	{
		NewLocation.X += (DeltaTime * 40.f); //todo set speed
		SetActorLocation(NewLocation);
		if (NewLocation.X > boundary)
		{
			float oldboundary=boundary;
			boundary = MinStep+FMath::FRandRange(-500.0f, +300.0f); //todo MinStep not working
			if (boundary > oldboundary) 
			{
				IsRotating = false;
			}
			
			else if (boundary < oldboundary) {
				IsRotating = true;
				Right = false;
			}
			
			first = true;
			UE_LOG(LogTemp, Log, TEXT("Boundary Right %f"), boundary);
			
		}
	}

	else if (!Right)
	{
		
		
		NewLocation.X -= (DeltaTime * 40.f);   //todo set speed 
		SetActorLocation(NewLocation);
		if (NewLocation.X < boundary)
		{
			float oldboundary = boundary;
			boundary =MinStep+ FMath::FRandRange(-500.0f, +300.0f); //todo MinStep not working
			if (boundary < oldboundary)
			{
				IsRotating = false;
			}
			else if (boundary > oldboundary) {
				Right = true;
				IsRotating = true;
			}
			
			
			first = true;
			UE_LOG(LogTemp, Log, TEXT("Boundary %f"), boundary);
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
		{		//FRotator Normalise = this->GetActorRotation();
				//Normalise.Yaw = -this->GetActorRotation().Yaw;
				//this->SetActorRotation(Normalise);
			IsRotating = false;
			first = true;
		}
		//UE_LOG(LogTemp, Log, TEXT("get Actor Rotation %f"), GetActorRotation().Yaw);
		//UE_LOG(LogTemp, Log, TEXT("set Actor Rotation %f"), ActorRotation.Yaw);
		
		//if ((FMath::RoundHalfToZero(ActorRotation.Yaw) == 0) || FMath::RoundHalfFromZero(ActorRotation.Yaw)>=359)
		//{
		//	ActorRotation.Yaw = 0.001f;
			//this->SetActorRotation(ActorRotation);
	//	}
		//IsRotating = false;
	
}
