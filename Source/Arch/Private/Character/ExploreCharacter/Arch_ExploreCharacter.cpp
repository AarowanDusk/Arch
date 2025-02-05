// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ExploreCharacter/Arch_ExploreCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"

AArch_ExploreCharacter::AArch_ExploreCharacter()
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); 
	CameraComponent->bUsePawnControlRotation = true;
}

void AArch_ExploreCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Controller == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Character has no Controller!"));
		return;
	}
	if (GetCharacterMovement() == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Character has no Movemenbt!"));
		return;
	}
	UE_LOG(LogTemp, Error, TEXT("EXPLORE: Velocity: %s"), *GetCharacterMovement()->Velocity.ToString());
}

void AArch_ExploreCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

