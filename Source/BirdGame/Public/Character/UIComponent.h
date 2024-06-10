// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UIComponent.generated.h"

class UUserWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BIRDGAME_API UUIComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUIComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> BaseUIClass;

	UUserWidget* SetUIWidget(TSubclassOf<UUserWidget> WidgetClass);

protected:
	UPROPERTY()
	UUserWidget* UIInstance;

	UPROPERTY()
	APlayerController* CurrentPlayer;

	// Called when the game starts
	virtual void BeginPlay() override;


		
};
