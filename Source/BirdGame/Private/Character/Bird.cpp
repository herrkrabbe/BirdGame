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

}

