// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbstractNest.generated.h"

UCLASS(Abstract)
class BIRDGAME_API AAbstractNest : public AActor
{
	GENERATED_BODY()
protected:
	// Sets default values for this actor's properties
	AAbstractNest();
public:	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Durability;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float Comfort;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
