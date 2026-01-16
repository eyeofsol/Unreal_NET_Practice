// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUDWidget.h"
#include "TestGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

void UMainHUDWidget::UpdateMyScore(int32 InScore)
{
	MyScoreText->SetText(FText::AsNumber(InScore));
}

void UMainHUDWidget::UpdateOtherScore(int32 InScore)
{
	OtherScoreText->SetText(FText::AsNumber(InScore));
}

void UMainHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GameOverText->SetVisibility(ESlateVisibility::Hidden);
}

void UMainHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!CachedGameState.IsValid())
	{
		CachedGameState = Cast<ATestGameState>(UGameplayStatics::GetGameState(this));
	}

	UpdateTimeDisplay();
	UpdateGameOverDisplay();
}

void UMainHUDWidget::UpdateTimeDisplay()
{
	if (CachedGameState.IsValid())
	{
		int32 Total = FMath::FloorToInt(CachedGameState->GetGameRemainingTime());
		int32 Minutes = Total / 60;
		int32 Seconds = Total % 60;
		RemainingTimeText->SetText(FText::FromString(FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds)));
	}
}

void UMainHUDWidget::UpdateGameOverDisplay()
{
	if (CachedGameState.IsValid() && CachedGameState->IsGameOver())
	{
		//ATestGameState* MyState = Cast<ATestGameState>(CachedGameState->PlayerArray[0]);
		//ATestGameState* OtherState = Cast<ATestGameState>(CachedGameState->PlayerArray[1]);
		GameOverText->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		GameOverText->SetVisibility(ESlateVisibility::Hidden);
	}
}
