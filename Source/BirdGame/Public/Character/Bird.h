// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "FlightQuaternion.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "Bird.generated.h"

UCLASS()
class BIRDGAME_API ABird : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABird();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* PlayerCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* BirdMesh;

	USkeletalMeshComponent* GetBirdMesh() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* BirdCollision;

	/*INPUT*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* IMC_Ground;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* JumpAction;


	APlayerController* BirdController;
	UEnhancedInputLocalPlayerSubsystem* Subsystem;


	/*ITEM*/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	bool HasItem = false;

	UFUNCTION(BlueprintCallable, Category = "Item")
	void SetHasItem(bool HasNewItem);

	UFUNCTION(BlueprintCallable, Category = "Item")
	bool GetHasItem();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool HasJumped = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool HasLanded = true;

	/*QUATERNION*/

	UFlightQuaternion* Quaternion;
	///////////////////////////////////////////////
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	
};
