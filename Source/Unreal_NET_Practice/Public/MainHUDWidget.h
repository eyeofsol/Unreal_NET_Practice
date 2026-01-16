// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHUDWidget.generated.h"

class UTextBlock;
class ATestGameState;

/**
 * 
 */
UCLASS()
class UNREAL_NET_PRACTICE_API UMainHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void UpdateMyScore(int32 InScore);

	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void UpdateOtherScore(int32 InScore);
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void UpdateTimeDisplay();

	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void UpdateGameOverDisplay();

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> RemainingTimeText = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> GameOverText = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> MyScoreText = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> OtherScoreText = nullptr;

private:
	TWeakObjectPtr<ATestGameState> CachedGameState = nullptr;
};
