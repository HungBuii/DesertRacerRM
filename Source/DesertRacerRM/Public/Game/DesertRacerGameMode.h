// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DesertRacerGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DESERTRACERRM_API ADesertRacerGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	/** Reset Level */
	void ResetLevel(bool _bIsWin);
	
private:
	/** Time Reset */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Time Reset Level", meta=(AllowPrivateAccess=true))
	float LoseGameTimeReset = 1.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Time Reset Level", meta=(AllowPrivateAccess=true))
	float WinGameTimeReset = 3.f;
	
	FTimerHandle ResetGameTimer;
	
	/** Reset Level */
	void OnResetGameTimerTimeout();
};
