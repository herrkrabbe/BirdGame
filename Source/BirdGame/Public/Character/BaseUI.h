// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseUI.generated.h"

class UCanvasPanel;
class UProgressBar;

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

protected:
	UPROPERTY(EditAnywhere, Category = "Organization", meta = (BindWidget))
	UCanvasPanel* RootCanvas;

};
