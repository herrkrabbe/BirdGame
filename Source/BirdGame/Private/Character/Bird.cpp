// Fill out your copyright notice in the Description page of Project Settings.



#include "Character/Bird.h"
#include "Engine/GameEngine.h"

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

/*TICK*/
void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetCharacterMovement()->IsFalling() == true) {
		IsFlying = true;
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("IS FLYING"));
		}
	}
	else {
		IsFlying = false;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("WALK"));
	}
}

/*MOVE*/
void ABird::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller != nullptr) {
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		//AddMovementInput(GetActorRightVector(), MovementVector.X);   if we decide to move to the left/right again
	}
	
}
/*JUMP/LIFT OFF*/
void ABird::Jump(const FInputActionValue& Value)
{
	//ONE WAY OF LIFTING 
	/*GetCharacterMovement()->MaxWalkSpeed = 150.0f;
	FVector JumpDirection = FVector::UpVector; 
	float JumpForce = 1000.0f; 
	GetCharacterMovement()->AddImpulse(JumpDirection * JumpForce);
	*/
	//AddMovementInput(GetActorForwardVector(), MovementVector.Y);

	//SECOND WAY OF LIFTING
	FVector UprojectedOnV = GetVelocity().ProjectOnTo(GetActorForwardVector());
	float VectorLength = UprojectedOnV.Size();
	float NewVelocity = VectorLength * 1000;
	GetCharacterMovement()->AddForce(NewVelocity * GetActorUpVector());
	if (IsFlying == true) {
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
		/*Ativate IMC_Bird to fly*/ //WORKS
		/*if (BirdController)
		{
			if (Subsystem) {
				IMC_Ground->Disable();

			}
		}*/
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("SWITCH IMC"));
		Land();
	}
	
	
}

/*LOOK AROUND*/
void ABird::LookAround(const FInputActionValue& Value)
{
	FVector2D LookAroundVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAroundVector.X);
		AddControllerPitchInput((LookAroundVector.Y));
	}
}


/*LAND*/
void ABird::Land()
{
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
	
	//probably do something like overlap with ground coliision or check if there is stuff from unreal to check if the bird is on the ground

	//switching back to IMC_Ground
	//IF THIS DELETES THE IMC, try using active index, so instead of 0 switch to 1 
	
}


/*DROP ITEM*/
void ABird::DropItem()
{
	SetHasItem(false);
	//Item->DetachFromBird(AAbstractItem * TargetCharacter);
	// https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/GameFramework/AActor/DetachFromActor
}


/*ROLL*/
void ABird::Roll(const FInputActionValue& Value)
{ 
	if (Controller)
	{
		//rotates the whole screen instead of just bird;
		/*FRotator ControlRotation = Controller->GetControlRotation();
		ControlRotation.Roll += 1.0f;
		FQuat QuatRotation = ControlRotation.Quaternion();
	 
		AddControllerRollInput(QuatRotation.Z);
		//AddControllerPitchInput((QuatRotation.Y));
		// Set the modified control rotation
		//BirdController->SetControlRotation(QuatRotation);
*/
		
		FVector RotationDegree = Value.Get<FVector>();
		float VectorLength = RotationDegree.Size();
		FRotator RollRotation = FRotator(0, 0, 0);
		RollRotation.Pitch = VectorLength;
		GetMesh()->AddLocalRotation(FQuat(RollRotation));
	}
}

void ABird::Fly(const FInputActionValue& Value)
{
	FVector UprojectedOnV = GetVelocity().ProjectOnTo(GetActorForwardVector());
	float VectorLength = UprojectedOnV.Size();
	float NewVelocity = VectorLength * 1000;
	GetCharacterMovement()->AddForce(NewVelocity * GetActorUpVector());
	if (IsFlying == true) {
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
		/*Ativate IMC_Bird to fly*/ //WORKS
		/*if (BirdController)
		{
			if (Subsystem) {
				IMC_Ground->Disable();

			}
		}*/
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
			Subsystem->AddMappingContext(IMC_Bird, 1);
		}
	}


	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABird::Move);
		EnhancedInputComponent->BindAction(LookAroundAction, ETriggerEvent::Triggered, this, &ABird::LookAround);
		//read comment below on the right 
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ABird::Jump);
		EnhancedInputComponent->BindAction(FlyAction, ETriggerEvent::Triggered, this, &ABird::Fly); //just pressed once instead of triggered?
		EnhancedInputComponent->BindAction(RollAction, ETriggerEvent::Triggered, this, &ABird::Roll);
		EnhancedInputComponent->BindAction(DropItemAction, ETriggerEvent::Triggered, this, &ABird::DropItem);
	}
	
}

