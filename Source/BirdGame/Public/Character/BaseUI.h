// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseUI.generated.h"

class UCanvasPanel;
/**
 * 
 */
UCLASS()
class BIRDGAME_API UBaseUI : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category = "Organization", meta = (BindWidget))
	UCanvasPanel* RootCanvas;
	
};
