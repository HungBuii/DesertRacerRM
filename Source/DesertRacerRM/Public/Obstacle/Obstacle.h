// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle.generated.h"

class UPaperSpriteComponent;
class UCapsuleComponent;

UCLASS()
class DESERTRACERRM_API AObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	AObstacle();

protected:
	virtual void BeginPlay() override;
	
public:
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	/** Collision */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UCapsuleComponent* CapsuleComp;
	
	/** Sprite */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UPaperSpriteComponent* ObstacleSprite;
	
	/** Finish Line? */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Is Finish Line?", meta=(AllowPrivateAccess=true))
	bool bFinishLine = false;
	
	/** Sound when other collision */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Sound", meta=(AllowPrivateAccess=true))
	USoundBase* HitSound;
};
