// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AAbstractItem.h"
#include "GameFramework/Actor.h"
#include "AItem.generated.h"




UCLASS()
class BIRDGAME_API AItem : public AAbstractItem
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Sets default values for this actor's properties
	AItem(const FObjectInitializer& ObjectInitializer);


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ItemMesh;


};
};
