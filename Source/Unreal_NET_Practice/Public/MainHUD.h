// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_NET_PRACTICE_API AMainHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	inline TWeakObjectPtr<UUserWidget> GetMainHUDWidget() const { return MainHUDWidget; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> MainHUDWidgetClass = nullptr;

private:
	UPROPERTY()
	TWeakObjectPtr<UUserWidget> MainHUDWidget = nullptr;
};
