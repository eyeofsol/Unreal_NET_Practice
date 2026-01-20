// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreActor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "TestPlayerState.h"
#include "TestGameState.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AScoreActor::AScoreActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetSphereRadius(100.0f);
	SetRootComponent(Collision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetupAttachment(Collision);
}

// Called when the game starts or when spawned
void AScoreActor::BeginPlay()
{
	Super::BeginPlay();

	if (!CachedGameState.IsValid())
	{
		CachedGameState = Cast<ATestGameState>(UGameplayStatics::GetGameState(this));
	}

	if (HasAuthority())
	{
		OnActorBeginOverlap.AddDynamic(this, &AScoreActor::OnOverlapEvent);
	}
}

void AScoreActor::OnOverlapEvent(AActor* OverlappedActor, AActor* OtherActor)
{
	if (HasAuthority())
	{
		ACharacter* Character = Cast<ACharacter>(OtherActor);
		if (Character)
		{
			ATestPlayerState* MyPS = Character->GetPlayerState<ATestPlayerState>();
			if (MyPS)
			{
				ATestPlayerState* PS1 = Cast<ATestPlayerState>(CachedGameState->PlayerArray[0]);
				ATestPlayerState* PS2 = Cast<ATestPlayerState>(CachedGameState->PlayerArray[1]);

				if (MyPS == PS1)
				{
					PS1->AddMyScore(Point);
					PS2->AddOtherScore(Point);
				}
				else if (MyPS == PS2)
				{
					PS2->AddMyScore(Point);
					PS1->AddOtherScore(Point);
				}
				Destroy();

			}
		}
	}
}

