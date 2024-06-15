// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Bird.h"

// Sets default values
ABird::ABird()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BirdMesh = GetBirdMesh();
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

void ABird::Pitch(FInputActionValue& pitch)
{
}

void ABird::Roll(FInputActionValue& roll)
{
}

float ABird::AddLift()
{
	return 0.0f;
}

