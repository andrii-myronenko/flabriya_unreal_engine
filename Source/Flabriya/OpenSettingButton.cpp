// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenSettingButton.h"
#include "PaperSpriteComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine.h"
#include "Grid.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "EngineUtils.h"

AOpenSettingButton::AOpenSettingButton() 
{
	PrimaryActorTick.bCanEverTick = true;

	OnClicked.AddUniqueDynamic(this, &AOpenSettingButton::OnSelected);
}

void AOpenSettingButton::OnSelected(AActor* Target, FKey ButtonPressed)
{
	if (bRespondsToClicks) 
	{
		FStringClassReference MyWidgetClassRef(TEXT("/Game/InGameWidgets/SettingsMenu.SettingsMenu_C"));
		APlayerController * MyPlayer = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (UClass* MyWidgetClass = MyWidgetClassRef.TryLoadClass<UUserWidget>())
		{
			AGrid::SetGridRespondable(false, GetWorld());
			AOpenSettingButton::SetButtonRespondable(false, GetWorld());
			UGameplayStatics::SetGamePaused(GetWorld(), true);
			UUserWidget* MyWidget = CreateWidget<UUserWidget>(MyPlayer, MyWidgetClass);
			MyWidget->AddToViewport();
		}
	}
}

void AOpenSettingButton::SetButtonRespondable(bool bIsRespondable, UWorld* World) 
{
	for (TObjectIterator<AOpenSettingButton> Itr; Itr; ++Itr)
	{
		if (Itr->GetWorld() != World)
		{
			continue;
		}
		Itr->bRespondsToClicks = bIsRespondable;
	}
}