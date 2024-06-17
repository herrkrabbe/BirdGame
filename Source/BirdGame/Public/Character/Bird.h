// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "InputMappingContext.h"
#include "Components/SphereComponent.h"
//#include "EnhancedInputComponent.h"
//#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
//#include "Components/InputComponent.h"
//#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Bird.generated.h"

struct FInputActionValue;
class UCameraComponent;
class UInputAction;
class InputComponent;
class InputAction;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* ItemCollision;

	USkeletalMeshComponent* GetBirdMesh() const;

	/*INPUT*/

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	//UInputMappingContext* IMC_Bird;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LiftAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* PitchAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* RollAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* YawAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* DropItemAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* FlapAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* SoarAction;


	/*ITEM */
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	bool HasItem = false;

	UFUNCTION(BlueprintCallable, Category = "Item")
	void SetHasItem(bool HasNewItem);

	UFUNCTION(BlueprintCallable, Category = "Item")
	bool GetHasItem();

	//APlayerController* PlayerController;
	//UEnhancedInputLocalPlayerSubsystem* Subsystem;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//AAbstractItem; 




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//APlayerController* BirdController;
	//UEnhancedInputLocalPlayerSubsystem* Subsystem;



private:
	void Pitch(const FInputActionValue& Value);
	void Roll(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void Yaw(const FInputActionValue& Value);
	float AddLift(const FInputActionValue& Value);

};
