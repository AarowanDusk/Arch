// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Marker/Arch_Actor.h"
#include "Components/WidgetComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Actor/Roof/Arch_RoofActor.h"

AArch_Actor::AArch_Actor()
{
	PrimaryActorTick.bCanEverTick = true;

    USceneComponent* Root = CreateDefaultSubobject<USceneComponent>("SceneRoot");
    SetRootComponent(Root);
}

void AArch_Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AArch_Actor::NotifyActorOnClicked(FKey ButtonPressed)
{
    Super::NotifyActorOnClicked(ButtonPressed);

    ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (!PlayerCharacter) return;

    FVector TargetLocation = GetActorLocation();

    FVector SafeLocation = TargetLocation + FVector(100.0f, 0.0f, 0.0f); 

    UCharacterMovementComponent* MoveComp = PlayerCharacter->FindComponentByClass<UCharacterMovementComponent>();
    if (MoveComp)
    {
        PlayerCharacter->GetController()->SetControlRotation((TargetLocation - PlayerCharacter->GetActorLocation()).Rotation());
        PlayerCharacter->SetActorLocation(SafeLocation, true);
    }

    SpawnRoof();
}

void AArch_Actor::SpawnRoof()
{
    if (RoofBPClass)
    {
        FVector Location = GetActorLocation();   
        FRotator Rotation = GetActorRotation();

        AArch_RoofActor* SpawnedRoof = GetWorld()->SpawnActor<AArch_RoofActor>(RoofBPClass, Location, Rotation);
        if (SpawnedRoof)
        {
            SpawnedRoof->ShowRoof();
        }
    }
}

