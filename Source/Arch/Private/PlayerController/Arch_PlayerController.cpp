// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/Arch_PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/BaseCharacter/Arch_BaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameModeBase/Arch_GameModeBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerStart.h"

void AArch_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AArch_PlayerController::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AArch_PlayerController::Look);
		EnhancedInputComponent->BindAction(PawnAction, ETriggerEvent::Triggered, this, &AArch_PlayerController::PawnChangeAction);
		EnhancedInputComponent->BindAction(ReturnAction, ETriggerEvent::Triggered, this, &AArch_PlayerController::ReturnToPlayerStart);

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AArch_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (this)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	CharacterReference = Cast<AArch_BaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	GameMode = Cast<AArch_GameModeBase>(GetWorld()->GetAuthGameMode());

	bShowMouseCursor = true; 
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void AArch_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (this == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Character has no Controller!"));
		return;
	}

	UE_LOG(LogTemp, Error, TEXT("Before: Velocity: %s"), *CharacterReference->GetCharacterMovement()->Velocity.ToString());
}

void AArch_PlayerController::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (this != nullptr)
	{
		CharacterReference->AddMovementInput(CharacterReference->GetActorForwardVector(), MovementVector.Y);
		CharacterReference->AddMovementInput(CharacterReference->GetActorRightVector(), MovementVector.X);
		UE_LOG(LogTemp, Warning, TEXT("Move: X=%f, Y=%f"), MovementVector.X, MovementVector.Y);

	}
}

void AArch_PlayerController::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (this != nullptr)
	{
		CharacterReference->AddControllerYawInput(LookAxisVector.X);
		CharacterReference->AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AArch_PlayerController::PawnChangeAction(const FInputActionValue& Value)
{
	if (GameMode)
	{
		if (bOldBool != bIsFirstPerson)
		{
			GameMode->SwitchPawn();
			CharacterReference = Cast<AArch_BaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			bOldBool = bIsFirstPerson;

			if (!bIsFirstPerson)
			{
				bShowMouseCursor = false;
				bEnableClickEvents = false;
				bEnableMouseOverEvents = false;
			}
			else
			{
				bShowMouseCursor = true;
				bEnableClickEvents = true;
				bEnableMouseOverEvents = true;
			}
		}
	}

	GetWorld()->GetTimerManager().SetTimer(ToggleViewTimerHandle, this, &AArch_PlayerController::ToggleFirstPersonView, 0.5f, false);
}

void AArch_PlayerController::ToggleFirstPersonView()
{
	bIsFirstPerson = !bIsFirstPerson;
}

void AArch_PlayerController::ReturnToPlayerStart(const FInputActionValue& Value)
{
	APawn* ControlledPawn = GetPawn();

	if (ControlledPawn)
	{
		APlayerStart* PlayerStart = Cast<APlayerStart>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass()));

		if (PlayerStart)
		{
			FVector StartLocation = PlayerStart->GetActorLocation();
			FRotator StartRotation = PlayerStart->GetActorRotation();

			ControlledPawn->SetActorLocationAndRotation(StartLocation, StartRotation);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Player Start not found!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Controlled Pawn Found!"));
	}
}
