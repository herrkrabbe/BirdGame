// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Bird.h"

// Sets default values
ABird::ABird()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//bUseControllerRotationYaw = true;
	//bUseControllerRotationPitch = false;
	//bUseControllerRotationRoll = false;

	//SceneRoot= CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	//RootComponent = SceneRoot;

	/*Collision*/
	BirdCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	//BirdCollision->SetupAttachment(SceneRoot);

	/*Mesh*/
	//BirdMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	//BirdMesh = GetMesh(); // GetBirdMesh();
	//BirdMesh->SetupAttachment(BirdCollision);
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FQuat(FRotator(0.0f, -90.0f, 0.0f)));

	
	/*Springarm*/
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraSpringArm->SetupAttachment(GetMesh());
	//CameraSpringArm->TargetArmLength = StartSpringArmDistance; // The  camera follows at this distance behind the character	
	CameraSpringArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	CameraSpringArm->bEnableCameraLag = true;//Makes the camera movement feel smoother
	//CameraSpringArm->bDoCollisionTest = false; 

	/*Camera Component*/
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	PlayerCamera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName); // , USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	//PlayerCamera->AttachToComponent(CameraSpringArm, FAttachmentTransformRules::KeepRelativeTransform);
	//PlayerCamera->bUsePawnControlRotation = true;

	
	//bUseControllerRotationYaw = false;
	
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
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
	
	//checking if rotation works. move to flight later. 
	//float QuaternionRotation = Quaternion->q.X;
	//const FRotator PitchRotation(QuaternionRotation,0.0f,0.0f );
	//AddMovementInput(GetActorRightVector(), PitchRotation.X);  OR RATHER AddMovementInput(FVector(q.X, 0.0f, 0.0f);

}

void ABird::Jump(const FInputActionValue& Value)
{
	//trigger fly IMC here 
	IsFlying = true;
	
	/*if (BirdController)
	{
		if (Subsystem)
		{
			//Subsystem->RemoveMappingContext(IMC_Ground);
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
		}
	}


	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	
	if (EnhancedInputComponent) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABird::Move);
		EnhancedInputComponent->BindAction(LookAroundAction, ETriggerEvent::Triggered, this, &ABird::LookAround);
		//read comment below on the right 
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ABird::Jump); //just pressed once instead of triggered?
	}
	
}

