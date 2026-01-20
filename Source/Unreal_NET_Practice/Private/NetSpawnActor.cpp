// Fill out your copyright notice in the Description page of Project Settings.


#include "NetSpawnActor.h"
#include "ScoreActor.h"
#include "Kismet/GameplayStatics.h"
#include "TestGameState.h"

// Sets default values
ANetSpawnActor::ANetSpawnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;
}

// Called when the game starts or when spawned
void ANetSpawnActor::BeginPlay()
{
	Super::BeginPlay();

	if (!CachedGameState.IsValid())
	{
		CachedGameState = Cast<ATestGameState>(UGameplayStatics::GetGameState(this));
	}
	if (HasAuthority())
	{
		GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ANetSpawnActor::SpawnScoreActor, SpawnInterval, true);
	}
}

void ANetSpawnActor::SpawnScoreActor()
{
	if (ScoreActorClass && !CachedGameState->IsGameOver())
	{
		FVector RandomLocation = GetActorLocation();
		RandomLocation.X += FMath::RandRange(-SpawnRadius, SpawnRadius);
		RandomLocation.Y += FMath::RandRange(-SpawnRadius, SpawnRadius);
		RandomLocation.Z = 100.0f;

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		// 서버에서 스폰 (ScoreActor의 bReplicates가 true여야 클라이언트에 보임)
		GetWorld()->SpawnActor<AScoreActor>(ScoreActorClass, RandomLocation, FRotator::ZeroRotator, SpawnParams);
	}
}
