// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UIComponent.generated.h"

class UUserWidget;
class UBaseUI;

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
	TSubclassOf<UBaseUI> BaseUIClass;

	UUserWidget* SetUIWidget(TSubclassOf<UBaseUI> WidgetClass);

	UFUNCTION(BlueprintCallable, Category = "UI")
	FORCEINLINE UBaseUI* GetUIWidget() { return UIInstance; };

	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateHealth(float HealthPercentage);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateComfort(float ComfortPercentage);

protected:
	UPROPERTY()
	UBaseUI* UIInstance;

	UPROPERTY()
	APlayerController* CurrentPlayer;

	// Called when the game starts
	virtual void BeginPlay() override;


		
};
