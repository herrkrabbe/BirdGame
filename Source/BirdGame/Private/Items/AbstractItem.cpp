// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/AbstractItem.h"
#include "Components/SphereComponent.h"
#include "Engine/EngineTypes.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AAbstractItem::AAbstractItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ItemCollision"));
	RootComponent = ItemMesh;
	ItemCollision->SetupAttachment(RootComponent);

	ItemMesh->SetCollisionResponseToAllChannels(ECR_Block);
	ItemMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	ItemCollision->SetGenerateOverlapEvents(true);
	ItemCollision->SetCollisionResponseToAllChannels(ECR_Overlap);
}

// Called when the game starts or when spawned
void AAbstractItem::BeginPlay()
{
	Super::BeginPlay();
	ItemCollision->OnComponentBeginOverlap.AddDynamic(this, &AAbstractItem::OnBeginOverlap);
}

// Called every frame
void AAbstractItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAbstractItem::AttachComponentToBird(ABird* TargetCharacter)
{
	Bird = TargetCharacter;
	if (Bird != nullptr || Bird->GetHasItem())
	{
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true); //SnapToTargetNotIncludingScale
		AttachToComponent(Bird->GetMesh(), AttachmentRules, FName(TEXT("AttachSocket")));

		Bird->SetHasItem(true);
	}

	/*if (APlayerController* BirdController = Cast<APlayerController>(Bird->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(BirdController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(Bird->IMC_Ground, 3);
		}
		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(BirdController->InputComponent);

		if (EnhancedInputComponent)
		{
			EnhancedInputComponent->BindAction(Bird->DropItemAction, ETriggerEvent::Triggered, this, &AAbstractItem::Bird->DropItem);
		}
	}*/

}

void AAbstractItem::DetachFromBird(ABird* TargetCharacter)
{
	Bird = TargetCharacter;
	if (Bird != nullptr || Bird->GetHasItem())
	{
		FDetachmentTransformRules DetachmentRules(EDetachmentRule::KeepRelative, true); //SnapToTargetNotIncludingScale
		//DetachFromComponent(Bird->GetMesh(), DetachmentRules));

		Bird->SetHasItem(false);
	}

}


void AAbstractItem::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Bird = Cast<ABird>(OtherActor);
	if (Bird != nullptr)
	{
		AttachComponentToBird(Bird);

	}

}

