// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "TestCharacter.h"
#include "MainHUD.h"
#include "MainHUDWidget.h"

void ATestPlayerState::AddMyScore(int32 Point)
{
	if (HasAuthority())
	{
		MyScore += Point;
		OnRep_MyScore();
	}
}

void ATestPlayerState::AddOtherScore(int32 Point)
{
	if (HasAuthority())
	{
		OtherScore += Point;
		OnRep_OtherScore();
	}
}

void ATestPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATestPlayerState, MyScore);
	DOREPLIFETIME(ATestPlayerState, OtherScore);
}

void ATestPlayerState::OnRep_MyScore()
{
	UE_LOG(LogTemp, Log, TEXT("[%d]Score : %d"), GetPlayerId(), MyScore);
	if (!MainHUDWidget.IsValid())
	{
		if (GetPlayerController())
		{
			AMainHUD* HUD = GetPlayerController()->GetHUD<AMainHUD>();
			if (HUD && HUD->GetMainHUDWidget().IsValid())
			{
				MainHUDWidget = Cast<UMainHUDWidget>(HUD->GetMainHUDWidget().Get());
			}
		}
	}
	if (MainHUDWidget.IsValid())
	{
		MainHUDWidget->UpdateMyScore(MyScore);
	}
}

void ATestPlayerState::OnRep_OtherScore()
{
	UE_LOG(LogTemp, Log, TEXT("[%d]Score : %d"), GetPlayerId(), OtherScore);
	if (!MainHUDWidget.IsValid())
	{
		if (GetPlayerController())
		{
			AMainHUD* HUD = GetPlayerController()->GetHUD<AMainHUD>();
			if (HUD && HUD->GetMainHUDWidget().IsValid())
			{
				MainHUDWidget = Cast<UMainHUDWidget>(HUD->GetMainHUDWidget().Get());
			}
		}
	}
	if (MainHUDWidget.IsValid())
	{
		MainHUDWidget->UpdateOtherScore(OtherScore);
	}
}
