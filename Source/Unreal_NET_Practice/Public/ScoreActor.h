// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScoreActor.generated.h"

class USphereComponent;
class ATestGameState;

UCLASS()
class UNREAL_NET_PRACTICE_API AScoreActor : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AScoreActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapEvent(AActor* OverlappedActor, AActor* OtherActor);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USphereComponent> Collision = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Mesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	int32 Point = 10;

private:
	TWeakObjectPtr<ATestGameState> CachedGameState = nullptr;
};
