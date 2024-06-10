// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UIComponent.h"
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

UUserWidget* UUIComponent::SetUIWidget(TSubclassOf<UUserWidget> WidgetClass)
{
	if (!UIInstance && !(UIInstance->IsA(WidgetClass)))
	{
		UIInstance = CreateWidget<UUserWidget>(CurrentPlayer, WidgetClass);
		UIInstance->AddToViewport();
	}
	return UIInstance;
}

