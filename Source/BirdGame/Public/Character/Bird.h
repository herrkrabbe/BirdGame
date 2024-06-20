// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
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
#include "Math/Quat.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "Components/SceneComponent.h"
#include "Bird.generated.h"

UCLASS()
class BIRDGAME_API ABird : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABird();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* PlayerCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	USpringArmComponent* CameraSpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	USphereComponent* BirdCollision;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	//float StartSpringArmDistance = 300.0f;

	/*INPUT*/
	/*Ground*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* IMC_Ground;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAroundAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* DropItemAction;

	/*Air*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* IMC_Bird;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* PitchAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* RollAction;


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
	bool IsFlying = false;

	

	/*QUATERNION*/

	UFlightQuaternion* Quaternion;
	float RotationSpeed = 1000.f;
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
	void LookAround(const FInputActionValue& Value);
	void Land();
	void DropItem();
	void Roll();
};
