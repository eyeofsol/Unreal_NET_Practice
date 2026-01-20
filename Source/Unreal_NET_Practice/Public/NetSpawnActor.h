// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NetSpawnActor.generated.h"

class AScoreActor;
class ATestGameState;

UCLASS()
class UNREAL_NET_PRACTICE_API ANetSpawnActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANetSpawnActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnScoreActor();

protected:
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<AScoreActor> ScoreActorClass;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float SpawnInterval = 3.0f;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float SpawnRadius = 1000.0f;

private:
	FTimerHandle SpawnTimerHandle;
	TWeakObjectPtr<ATestGameState> CachedGameState = nullptr;
};
