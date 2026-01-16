// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TestPlayerState.generated.h"

class UMainHUDWidget;

/**
 * 
 */
UCLASS()
class UNREAL_NET_PRACTICE_API ATestPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddMyScore(int32 Point);

	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddOtherScore(int32 Point);

	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetMyScore() const { return MyScore; }

	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetOtherScore() const { return OtherScore; }

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_MyScore();

	UFUNCTION()
	void OnRep_OtherScore();

protected:
	UPROPERTY(ReplicatedUsing = OnRep_MyScore, BlueprintReadOnly, Category = "Data")
	int32 MyScore = 0;

	UPROPERTY(ReplicatedUsing = OnRep_OtherScore, BlueprintReadOnly, Category = "Data")
	int32 OtherScore = 0;

	TWeakObjectPtr<UMainHUDWidget> MainHUDWidget = nullptr;
};
