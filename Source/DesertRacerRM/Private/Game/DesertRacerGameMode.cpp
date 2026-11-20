// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/DesertRacerGameMode.h"

#include "Kismet/GameplayStatics.h"

void ADesertRacerGameMode::ResetLevel(bool _bIsWin)
{
	float Timer = LoseGameTimeReset;
	if (_bIsWin)
	{
		Timer = WinGameTimeReset;
	}
	
	GetWorldTimerManager().SetTimer(ResetGameTimer, this, &ADesertRacerGameMode::OnResetGameTimerTimeout,
		1.0f, false, Timer);
}

void ADesertRacerGameMode::OnResetGameTimerTimeout()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("InGame"));
}
