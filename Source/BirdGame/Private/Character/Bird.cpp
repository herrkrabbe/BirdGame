// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Bird.h"

// Sets default values
ABird::ABird()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BirdMesh = GetBirdMesh();

	BirdCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ItemCollision"));
	RootComponent = BirdMesh;
	BirdCollision->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void ABird::BeginPlay()
{
	Super::BeginPlay();



}

void ABird::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), MovementVector.Y);
	AddMovementInput(GetActorRightVector(), MovementVector.X);

	//checking if rotation works. move to flight later. 
	//float QuaternionRotation = Quaternion->q.X;
	//const FRotator PitchRotation(QuaternionRotation,0.0f,0.0f );
	//AddMovementInput(GetActorRightVector(), PitchRotation.X);  OR RATHER AddMovementInput(FVector(q.X, 0.0f, 0.0f);

}

void ABird::Jump(const FInputActionValue& Value)
{
	//trigger fly IMC here 
	//bool HasJumped = true;
	//bool HasLanded = false;
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

// Called every frame
void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	
	if (EnhancedInputComponent) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABird::Move);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ABird::Jump);
	}
	
}

