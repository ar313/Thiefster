// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterThief.generated.h"

UCLASS()
class THIEFSTER_API ACharacterThief : public ACharacter
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere)
		class UCameraComponent* SideViewCameraComponent;

		UPROPERTY(EditAnywhere)
		class USpringArmComponent* CameraBoom;
public:
	// Sets default values for this character's properties
	ACharacterThief();

	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveRight(float Value);
	void MoveUp(float Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	
	
};
