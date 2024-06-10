// Fill out your copyright notice in the Description page of Project Settings.


#include "AAbstractItem.h"

// Sets default values
AAAbstractItem::AAAbstractItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAAbstractItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAAbstractItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

