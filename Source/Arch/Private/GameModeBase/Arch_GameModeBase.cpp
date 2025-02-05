// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeBase/Arch_GameModeBase.h"
#include "Character/ExploreCharacter/Arch_ExploreCharacter.h"
#include "Character/FirstPerson/Arch_FirstPersonCharacter.h"
#include "PlayerController/Arch_PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"

AArch_GameModeBase::AArch_GameModeBase()
{
    bIsFirstPerson = false;
}

void AArch_GameModeBase::SwitchPawn()
{
    if (!GetWorld() || !GetWorld()->GetFirstPlayerController())
        return;

    AArch_PlayerController* PlayerController = Cast<AArch_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
    if (!PlayerController)
        return;

    APawn* CurrentPawn = PlayerController->GetPawn();
    if (!CurrentPawn)
        return;

    APawn* NewPawn = nullptr;

    if (bIsFirstPerson)
    {
        if (ExploreCharacter)
        {
            UE_LOG(LogTemp, Warning, TEXT("Switching to ExploreCharacter"));

            FActorSpawnParameters SpawnParams;
            SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
            NewPawn = GetWorld()->SpawnActor<APawn>(ExploreCharacter, CurrentPawn->GetActorLocation(), CurrentPawn->GetActorRotation(), SpawnParams);
        }
    }
    else
    {
        if (FirstPersonCharacter)
        {
            UE_LOG(LogTemp, Warning, TEXT("Switching to FirstPersonCharacter"));

            FActorSpawnParameters SpawnParams;
            SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
            NewPawn = GetWorld()->SpawnActor<APawn>(FirstPersonCharacter, CurrentPawn->GetActorLocation(), CurrentPawn->GetActorRotation(), SpawnParams);
        }
    }

    if (NewPawn)
    {
        PlayerController->UnPossess();
        PlayerController->Possess(NewPawn);

        if (UCharacterMovementComponent* MovementComp = NewPawn->FindComponentByClass<UCharacterMovementComponent>())
        {
            MovementComp->StopMovementImmediately();
            MovementComp->SetMovementMode(MOVE_Walking);
        }

        if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            InputSubsystem->ClearAllMappings();
            InputSubsystem->AddMappingContext(DefaultMappingContext, 0);
        }

        CurrentPawn->Destroy();

        bIsFirstPerson = !bIsFirstPerson;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to spawn new pawn!"));
    }
}
