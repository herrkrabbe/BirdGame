// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "InputMappingContext.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
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

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	//UInputMappingContext* IMC_Bird;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* ItemCollision;

	bool HasItem();
	//AAbstractItem* GetItem();
	//bool SetItem(AAbstractItem*); 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//AAbstractItem; 




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void Pitch(FInputActionValue& Value);
	void Roll(FInputActionValue& Value);
	float AddLift();



};
