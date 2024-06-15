// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/AbstractItem.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class BIRDGAME_API AItem : public AAbstractItem
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Sets default values for this actor's properties
	AItem();


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
