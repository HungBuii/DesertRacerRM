// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle/Obstacle.h"

#include "PaperSpriteComponent.h"
#include "Components/CapsuleComponent.h"

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
	
}


