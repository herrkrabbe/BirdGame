// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Bird.h"


// Sets default values
ABird::ABird()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BirdMesh = GetBirdMesh();
	//BirdMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ItemCollision"));
	RootComponent = BirdMesh;
	ItemCollision->SetupAttachment(RootComponent);
	//BirdMesh->SetGenerateOverlapEvents(true);
}

USkeletalMeshComponent* ABird::GetBirdMesh() const
{
	return BirdMesh;
}

void ABird::SetHasItem(bool HasNewItem)
{
	HasItem = HasNewItem;
}

bool ABird::GetHasItem()
{
	return HasItem;
}

// Called when the game starts or when spawned
void ABird::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABird::Pitch(const FInputActionValue& Value)
{
	//pitch is current rotation y?
	FVector2D PitchVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerPitchInput((PitchVector.Y));

	}
	
}

void ABird::Roll(const FInputActionValue& Value)
{
	//roll is current rotation x?
	FVector2D RollVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput((RollVector.X));

	}
}


void ABird::Yaw(const FInputActionValue& Value)
{
	//current rotation z
	FVector2D YawVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		//AddControllerYawInput((YawVector.Z));

	}
}


float ABird::AddLift(const FInputActionValue& Value)
{
	FVector2D LiftVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), LiftVector.Y);

	}
	return 0.0f;
}

