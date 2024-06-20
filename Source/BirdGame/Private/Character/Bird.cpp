// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Bird.h"

// Sets default values
ABird::ABird()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*Collision*/
	BirdCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	
	/*Mesh*/
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FQuat(FRotator(0.0f, -90.0f, 0.0f)));

	/*Springarm*/
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraSpringArm->SetupAttachment(GetMesh());
	CameraSpringArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	CameraSpringArm->bEnableCameraLag = true;//Makes the camera movement feel smoother
	//CameraSpringArm->bDoCollisionTest = false; 
	//CameraSpringArm->TargetArmLength = StartSpringArmDistance; // The  camera follows at this distance behind the character	

	/*Camera Component*/
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	PlayerCamera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName); // , USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	//PlayerCamera->AttachToComponent(CameraSpringArm, FAttachmentTransformRules::KeepRelativeTransform);
	//PlayerCamera->bUsePawnControlRotation = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bIgnoreBaseRotation = true;
}

// Called when the game starts or when spawned
void ABird::BeginPlay()
{
	Super::BeginPlay();

}

void ABird::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller != nullptr) {
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		//AddMovementInput(GetActorRightVector(), MovementVector.X);   if we decide to move to the left/right again
	}
	
}

void ABird::Jump(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
	FVector JumpDirection = FVector::UpVector; 
	float JumpForce = 10.0f; 
	GetCharacterMovement()->AddForce(JumpDirection * JumpForce);
	//AddMovementInput(GetActorForwardVector(), MovementVector.Y);

	IsFlying = true;
	
	FVector UprojectedOnV = GetVelocity().ProjectOnTo(GetActorForwardVector());
	float VectorLength = UprojectedOnV.Size();
	float NewVelocity = VectorLength * 1000;
	GetCharacterMovement()->AddForce(NewVelocity * GetActorUpVector());

	if (IsJumpProvidingForce()) {
		float AirControl = 1;
		GetCharacterMovement()->MaxFlySpeed = 10000.0f;
	}

	//AddMovementInput(GetActorForwardVector(), VectorLength.Y);

	/*Ativate IMC_Bird to fly*/ //WORKS
	/*if (BirdController)
	{
		if (Subsystem)
		{
			Subsystem->RemoveMappingContext(IMC_Ground);
			Subsystem->AddMappingContext(IMC_Bird, 0);
			
		}
	}*/
}

void ABird::LookAround(const FInputActionValue& Value)
{
	FVector2D LookAroundVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAroundVector.X);
		AddControllerPitchInput((LookAroundVector.Y));
	}
}

void ABird::Land()
{
	IsFlying = false;
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
	if (GetCharacterMovement()->IsMovingOnGround()) {
		if (BirdController)
		{
			if (Subsystem)
			{
				Subsystem->RemoveMappingContext(IMC_Bird);
				Subsystem->AddMappingContext(IMC_Ground, 0);

			}
		}
	}
	//probably do something like overlap with ground coliision or check if there is stuff from unreal to check if the bird is on the ground

	//switching back to IMC_Ground
	//IF THIS DELETES THE IMC, try using active index, so instead of 0 switch to 1 
	
}

void ABird::DropItem()
{
	SetHasItem(false);
	// https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/GameFramework/AActor/DetachFromActor
}

void ABird::Roll()
{ 
	/*const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Pitch, 0);

	// Get right vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
*/

	float Roll = InputComponent->GetAxisValue("RotateActorY");
	const FRotator RollRotation(0.0f, Roll*RotationSpeed, 0.0f);
	FQuat QuatRotation = RollRotation.Quaternion();

	if (Controller != nullptr) {
		//AddMovementInput(GetActorForwardVector(), PitchRotation.Y);
		
		AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None); //with quat
	}
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
	BirdController = Cast<APlayerController>(Controller);
	Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(BirdController->GetLocalPlayer());

	//Adding the Input Context
	if (BirdController)
	{
		if (Subsystem)
		{
			Subsystem->AddMappingContext(IMC_Ground, 0);
			//Subsystem->AddMappingContext(IMC_Bird, 1);
		}
	}


	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	
	if (EnhancedInputComponent) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABird::Move);
		EnhancedInputComponent->BindAction(LookAroundAction, ETriggerEvent::Triggered, this, &ABird::LookAround);
		//read comment below on the right 
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ABird::Jump); //just pressed once instead of triggered?
		EnhancedInputComponent->BindAction(RollAction, ETriggerEvent::Triggered, this, &ABird::Roll);

	}
	
}

