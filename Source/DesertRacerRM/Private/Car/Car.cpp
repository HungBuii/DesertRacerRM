// Fill out your copyright notice in the Description page of Project Settings.


#include "Car/Car.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PaperSpriteComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

ACar::ACar()
{
	PrimaryActorTick.bCanEverTick = false;
	
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	
	CarSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("CarSprite"));
	CarSprite->SetupAttachment(RootComponent);
}

void ACar::BeginPlay()
{
	Super::BeginPlay();
	
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>
														(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void ACar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACar::Move);
	}
}

void ACar::Move(const FInputActionValue& Value)
{
	FVector2D MoveActionValue = Value.Get<FVector2D>();
	GEngine->AddOnScreenDebugMessage(1, 10.0f, FColor::White, MoveActionValue.ToString());
	
	if (abs(MoveActionValue.Y) > 0)
	{
		float FinalSpeed = Speed;
		
		if (MoveActionValue.Y < 0)
		{
			FinalSpeed = Speed / 2;
		}
		
		if (abs(MoveActionValue.X) > 0)
		{
			float RotationAmount = -RotationSpeed * MoveActionValue.X * GetWorld()->DeltaTimeSeconds;
			
			if ((MoveActionValue.X < 0 && MoveActionValue.Y < 0) || 
				(MoveActionValue.X > 0 && MoveActionValue.Y < 0))
			{
				RotationAmount = -RotationAmount;
			}
			
			FRotator NewRotator(RotationAmount , 0.f, 0.f);
			AddActorWorldRotation(NewRotator);
		}
		
		/* GetActorUpVector(): lấy hướng (direction) Z "cục bộ (local)" để sử dụng trong "space world" (world). 
		 *					   Nên sử dụng cả function k nên tách thành GetActorUpVector().Z,... bởi vì 
		 *					   nó còn phải phụ thuộc vào 2 trục còn lại và độ xoay (rotation) của các trục đó trong "world" 
		 *					   được thiết lập sẵn trong function đó 
		 */
		
		FVector CurrentLocation = GetActorLocation();
		FVector DistanceToMove = GetActorUpVector() * FinalSpeed * MoveActionValue.Y * GetWorld()->DeltaTimeSeconds;
		FVector NewLocation = CurrentLocation + DistanceToMove;
		SetActorLocation(NewLocation);
		
		UE_LOG(LogTemp, Warning, TEXT("Final Speed: %f"), FinalSpeed);
	}
}

