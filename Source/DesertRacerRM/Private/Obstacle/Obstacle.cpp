// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle/Obstacle.h"

#include "PaperSpriteComponent.h"
#include "Car/Car.h"
#include "Components/CapsuleComponent.h"
#include "Game/DesertRacerGameMode.h"
#include "Kismet/GameplayStatics.h"

AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = false;
	
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);
	
	ObstacleSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("ObstacleSprite"));
	ObstacleSprite->SetupAttachment(RootComponent);
}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OverlapBegin);
	
}

void AObstacle::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ACar* Car = Cast<ACar>(OtherActor))
	{
		Car->SetCanMove(false);
		UGameplayStatics::PlaySound2D(GetWorld(), HitSound);
		
		if (ADesertRacerGameMode* DesertRacerGameMode = Cast<ADesertRacerGameMode>
												(UGameplayStatics::GetGameMode(GetWorld())))
		{
			DesertRacerGameMode->ResetLevel(bFinishLine);
		}
	}
}


