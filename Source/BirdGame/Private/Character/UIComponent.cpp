// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UIComponent.h"
#include "Character/BaseUI.h"
#include "Components/ProgressBar.h"
#include "Blueprint/UserWidget.h"

// Sets default values for this component's properties
UUIComponent::UUIComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUIComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (!CurrentPlayer)
	{
		APawn* Owner = Cast<APawn>(GetOwner());
		CurrentPlayer = Cast<APlayerController>(Owner->GetController());
	}
	if (BaseUIClass)
	{
		SetUIWidget(BaseUIClass);
	}
}


// Called every frame
void UUIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

UUserWidget* UUIComponent::SetUIWidget(TSubclassOf<UBaseUI> WidgetClass)
{
	if (!UIInstance || !(UIInstance->IsA(WidgetClass)))
	{
		UIInstance = CreateWidget<UBaseUI>(CurrentPlayer, WidgetClass);
		UIInstance->AddToViewport();

		if (WingFlap && SpentWingFlap)
		{
			UIInstance->SetFlapsTexture(WingFlap, SpentWingFlap);
			UIInstance->SetWingFlapsMax(3);
		}
	}
	return UIInstance;
}

void UUIComponent::UpdateHealth(float HealthPercentage)
{
	UIInstance->NestHealth->SetPercent(HealthPercentage);
}

void UUIComponent::UpdateComfort(float ComfortPercentage)
{
	UIInstance->NestComfort->SetPercent(ComfortPercentage);
}

void UUIComponent::SetMaxFlaps(int NewMax)
{
	UIInstance->SetWingFlapsMax(NewMax);
}

void UUIComponent::SetCurrentFlaps(int NewFlaps)
{
	UIInstance->SetCurrentFlaps(NewFlaps);
}

