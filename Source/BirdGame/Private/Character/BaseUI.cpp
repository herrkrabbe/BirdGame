// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseUI.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Blueprint/WidgetTree.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"

void UBaseUI::SetFlapsTexture(UTexture2D* EnabledFlap, UTexture2D* DisabledFlap)
{
	FlapTexture = EnabledFlap;
	NoFlapTexture = DisabledFlap;
}

void UBaseUI::SetWingFlapsMax(int NewMax)
{
	int FlapDelta = NewMax - WingFlaps->GetChildrenCount();
	if (FlapDelta == 0)
		return;

	if (FlapDelta > 0)
	{
		for (size_t i = 0; i < FlapDelta; i++)
		{
			UImage* FlapWidget = WidgetTree->ConstructWidget<UImage>();
			FlapWidget->SetBrushFromTexture(FlapTexture, true);
			UHorizontalBoxSlot* WidgetSlot = WingFlaps->AddChildToHorizontalBox(FlapWidget);
			WidgetSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
		}
	}
	else
	{
		for (size_t i = 0; i < -FlapDelta; i++)
		{
			WingFlaps->RemoveChildAt(WingFlaps->GetChildrenCount() - 1);
		}
	}
}

void UBaseUI::SetCurrentFlaps(int NewFlaps)
{
	int MaxFlaps = WingFlaps->GetChildrenCount();
	int CurrentFlaps = NewFlaps > MaxFlaps ? MaxFlaps : NewFlaps < 1 ? 1 : NewFlaps;
	for (size_t i = 0; i < CurrentFlaps; i++)
	{
		if (UImage* FlapWidget = Cast<UImage>(WingFlaps->GetChildAt(i)))
		{
			FlapWidget->SetBrushFromTexture(FlapTexture);
		}
	}

	if (CurrentFlaps == MaxFlaps)
		return;

	for (size_t i = CurrentFlaps; i < MaxFlaps; i++)
	{
		if (UImage* FlapWidget = Cast<UImage>(WingFlaps->GetChildAt(i)))
		{
			FlapWidget->SetBrushFromTexture(NoFlapTexture);
		}
	}
}
