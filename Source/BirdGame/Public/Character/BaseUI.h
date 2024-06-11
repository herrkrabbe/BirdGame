// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseUI.generated.h"

class UCanvasPanel;
class UProgressBar;
class UHorizontalBox;

/**
 * 
 */
UCLASS()
class BIRDGAME_API UBaseUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Nest", meta = (BindWidget))
	UProgressBar* NestHealth;

	UPROPERTY(EditAnywhere, Category = "Nest", meta = (BindWidget))
	UProgressBar* NestComfort;



	UFUNCTION(BlueprintCallable, Category = "Flight")
	void SetFlapsTexture(UTexture2D* EnabledFlap, UTexture2D* DisabledFlap);

	UFUNCTION(BlueprintCallable, Category = "Flight")
	void SetWingFlapsMax(int NewMax);

	UFUNCTION(BlueprintCallable, Category = "Flight")
	void SetCurrentFlaps(int NewFlaps);


protected:
	UPROPERTY(EditAnywhere, Category = "Organization", meta = (BindWidget))
	UCanvasPanel* RootCanvas;
	
	UPROPERTY()
	UTexture2D* FlapTexture;
	UPROPERTY()
	UTexture2D* NoFlapTexture;

	UPROPERTY(EditAnywhere, Category = "Flight", meta = (BindWidget))
	UHorizontalBox* WingFlaps;
};
