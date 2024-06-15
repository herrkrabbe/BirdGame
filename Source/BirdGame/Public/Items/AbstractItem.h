// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BirdGame/Public/Character/Bird.h"
#include "AbstractItem.generated.h"


UCLASS(Abstract)
class BIRDGAME_API AAbstractItem : public AActor
{
	GENERATED_BODY()
protected:
	// Sets default values for this actor's properties
	AAbstractItem();
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool PickedUp = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float myDurability = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float myComfort = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	class UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	class USphereComponent* ItemCollision;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	ABird* Bird;
	UFUNCTION(Blueprintable, BlueprintCallable, Category = "WeaponModel")
	void AttachComponentToPlayer(ABird* TargetCharacter);

};
