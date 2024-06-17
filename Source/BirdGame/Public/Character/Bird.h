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

	/*ITEM*/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	bool HasItem = false;

	UFUNCTION(BlueprintCallable, Category = "Item")
	void SetHasItem(bool HasNewItem);

	UFUNCTION(BlueprintCallable, Category = "Item")
	bool GetHasItem();

	///////////////////////////////////////////////
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	
};
