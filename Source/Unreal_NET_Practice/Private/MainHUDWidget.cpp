// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUDWidget.h"
#include "TestGameState.h"
#include "TestPlayerState.h"
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
	MyScoreText->SetText(FText::AsNumber(0));
	OtherScoreText->SetText(FText::AsNumber(0));
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
		APlayerController* PC = GetOwningPlayer();
		ATestPlayerState* MyState = PC->GetPlayerState<ATestPlayerState>();
		if (MyState)
		{
			if (MyState->GetMyScore() > MyState->GetOtherScore())
			{
				GameOverText->SetText(FText::FromString(FString::Printf(TEXT("승리!"))));
			}
			else if (MyState->GetMyScore() == MyState->GetOtherScore())
			{
				GameOverText->SetText(FText::FromString(FString::Printf(TEXT("무승부"))));
			}
			else
			{
				GameOverText->SetText(FText::FromString(FString::Printf(TEXT("패배"))));
			}
			GameOverText->SetVisibility(ESlateVisibility::HitTestInvisible);
		}
	}
	else
	{
		GameOverText->SetVisibility(ESlateVisibility::Hidden);
	}
}
